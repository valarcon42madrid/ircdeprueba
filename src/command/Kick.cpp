/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:36:03 by valarcon          #+#    #+#             */
/*   Updated: 2023/07/27 10:36:06 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Kick::Kick(Server* srv) : Command(srv) {}

Kick::~Kick() {}

// syntax: KICK <channel> <client> :[<message>]

void    Kick::execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "KICK"));
        return;
    }

    std::string name = args[0];
    std::string target = args[1];
    std::string reason = "No reason specified!";

    if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1))
    {
        reason = "";

        std::vector<std::string>::iterator it = args.begin();
        std::vector<std::string>::iterator end = args.end();

        while (it != end)
        {
			reason.append(*it + " ");
            it++;
        }
    }

    Channel *channel = client->get_channel();
    if (!channel || channel->get_name() != name)
    {
        client->reply(ERR_NOTONCHANNEL(client->get_nickname(), name));
        return;
    }

    if (channel->get_admin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), name));
        return;
    }

    Client *dest = _srv->get_client(target);
    if (!dest)
    {
        client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
        return;
    }

    if (!dest->get_channel() || dest->get_channel() != channel)
    {
        client->reply(ERR_USERNOTINCHANNEL(client->get_nickname(), dest->get_nickname(), name));
        return;
    }

    channel->kick(client, dest, reason);
}
