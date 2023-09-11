/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:37:15 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/11 18:04:09 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Notice::Notice(Server* srv) : Command(srv) {}

Notice::~Notice() {}

// syntax: NOTICE <msgtarget> <message>

void    Notice::execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2 || args[0].empty() || args[1].empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "NOTICE"));
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

	if (_srv->get_channel(target) != NULL)
    {
		Channel* channel = _srv->get_channel(target);
        if (!channel && _srv->get_client(target) == NULL)
        {
            client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), target));
			return;
        }
        if (channel->ext_msg())
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

            if (it == end)
            {
                client->reply(ERR_CANNOTSENDTOCHAN(client->get_nickname(), target));
                return;
            }
        }

        channel->broadcast(RPL_NOTICE(target, client->get_prefix(), message), client);
        return;
    }

    Client  *dest = _srv->get_client(target);
    if (!dest)
    {
        client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
		return;
    }

    dest->write(RPL_NOTICE(client->get_prefix(), target, message));
}
