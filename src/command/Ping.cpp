/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:38:19 by valarcon          #+#    #+#             */
/*   Updated: 2023/07/27 10:38:21 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Ping::Ping(Server* srv) : Command(srv) {}

Ping::~Ping() {}

// syntax: PING <server1> [<server2>]

void    Ping::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "PING"));
        return;
    }

    client->write(RPL_PING(client->get_prefix(), args.at(0)));
}
