/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:38:32 by valarcon          #+#    #+#             */
/*   Updated: 2023/07/27 10:38:35 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Pong::Pong(Server* srv) : Command(srv) {}

Pong::~Pong() {}

// syntax: PONG <server1> [<server2>]

void    Pong::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "PONG"));
        return;
    }

    client->write(RPL_PING(client->get_prefix(), args.at(0)));
}
