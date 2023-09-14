/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:01:15 by sasalama          #+#    #+#             */
/*   Updated: 2023/09/14 10:01:17 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Invite::Invite(Server* srv) : Command(srv) {}

Invite::~Invite() {}

// syntax: Invite <client> <channel>

void    Invite::execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "INVITE"));
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
	    Channel *channel = _srv->get_channel(name);
		Client* clientinvited = _srv->get_client(target);


    if (!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), name));
        return;
    }
	if (channel != client->get_channel())
    {
        client->reply(ERR_NOTONCHANNEL(client->get_nickname(), name));
        return ;
    }
    if (!clientinvited)
    {
        client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
        return;
    }
	if (channel->is_ban_client(clientinvited))
	{
		client->reply(ERR_BANEDFROMCHAN(channel->get_name(), target));

		return ;
	}
	if (channel->is_invited(clientinvited))
	{
		client->reply(ERR_ALREADYINVITED(client->get_nickname(), target, name));
		return ;
	}
    channel->invite(client, clientinvited);
}
