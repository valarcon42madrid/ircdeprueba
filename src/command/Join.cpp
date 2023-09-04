/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:35:41 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/04 18:24:16 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Join::Join(Server* srv) : Command(srv) {}

Join::~Join() {}

// syntax: JOIN <channels> [<keys>]

void    Join::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "JOIN"));
        return;
    }

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";
	std::string topic = "";

    Channel *channel = client->get_channel();
	if (channel) 
    {
		client->reply(ERR_TOOMANYCHANNELS(client->get_nickname(), name));
		return;
	}

    channel = _srv->get_channel(name);
	if (!channel)
		channel = _srv->create_channel(name, pass, topic, client);

    if (channel->get_limit() > 0 && channel->get_size() >= channel->get_limit())
    {
		client->reply(ERR_CHANNELISFULL(client->get_nickname(), name));
		return;
	}
	if (channel->is_ban_client(client))
    {
        client->reply(ERR_BANNEDFROMCHAN(client->get_nickname(), channel->get_name()));
        return ;
    }
	if (channel->is_invited(client))
	{
		client->join(channel);
		return ;
	}
	if (channel->get_invite() && pass == "+i")
    {
		if (channel->client_at_waitlist(client))
			client->reply(ERR_ALREADYONCHANNEL(client->get_nickname(), channel->get_name()));
		else
		{
			channel->client_to_waitlist(client);
			client->reply(RPL_INVITELIST(client->get_nickname(), channel->get_name()));

		}
		return ;
    }
    if (channel->get_key() != pass) 
    {
		client->reply(ERR_BADCHANNELKEY(client->get_nickname(), name));
		return;
	}
	if (channel->get_invite())
	{
		client->reply(ERR_INVITEONLYCHAN(client->get_nickname(), channel->get_name()));	
		return ;
	}
	client->join(channel);
}
