/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:39:04 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/11 17:55:44 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command/Command.hpp"

PrivMsg::PrivMsg(Server* srv) : Command(srv) {}

PrivMsg::~PrivMsg() {}

// syntax: PRIVMSG <msgtarget> :<message>

void    PrivMsg::execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2 || args[0].empty() || args[1].empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "PRIVMSG"));
        return;
    }

    std::string target = args.at(0);
    std::string message;

    std::vector<std::string>::iterator it = args.begin() + 1;
    std::vector<std::string>::iterator end = args.end();

    while (it != end)
    {
        message.append(*it + " ");
        it++;
    }

    if (message.at(0) == ':')
        message = message.substr(1);

    if (target.at(0) == '#' || _srv->get_channel(target))
    {
        Channel* channel = client->get_channel();

        if (!channel)
        {
            client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), target));
			return;
        }

        if (!channel->ext_msg())
        {
            std::vector<std::string> nicknames = channel->get_nicknames();

            std::vector<std::string>::iterator it = nicknames.begin();
            std::vector<std::string>::iterator end = nicknames.end();

            while (it != end)
            {
                if (*it == client->get_nickname())
                    break;

                it++;
            }

            if (it == end && _srv->get_channel(target)->ext_msg())
            {
                client->reply(ERR_CANNOTSENDTOCHAN(client->get_nickname(), target));
                return;
            }
        }

        channel->broadcast(RPL_PRIVMSG(target, client->get_prefix(), message), client);
        return;
    }


    Client  *dest = _srv->get_client(target);
    if (!dest)
    {
        client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
		return;
    }

    dest->write(RPL_PRIVMSG(client->get_prefix(), target, message));
}
