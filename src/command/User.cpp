/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:39:46 by valarcon          #+#    #+#             */
/*   Updated: 2023/07/27 10:39:51 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

User::User(Server* srv, bool auth) : Command(srv, auth) {}

User::~User() {}

// stntax: USER <username> <hostname> <servername> <realname>

void    User::execute(Client* client, std::vector<std::string> args)
{
    if (client->is_registered())
    {
        client->reply(ERR_ALREADYREGISTERED(client->get_nickname()));
        return;
    }

    if (args.size() < 4) 
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "USER"));
        return;
    }

    client->set_username(args[0]);
    client->set_realname(args[3]);
    client->welcome();
}
