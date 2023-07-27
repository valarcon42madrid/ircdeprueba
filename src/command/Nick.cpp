/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:36:49 by valarcon          #+#    #+#             */
/*   Updated: 2023/07/27 10:36:51 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Nick::Nick(Server* srv, bool auth) : Command(srv, auth) {}

Nick::~Nick() {}

// syntax: NICK <nickname>

void    Nick::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty()) 
    {
        client->reply(ERR_NONICKNAMEGIVEN(client->get_nickname()));
        return;
    }

    std::string nickname = args[0];

    if (_srv->get_client(nickname))
    {
        client->reply(ERR_NICKNAMEINUSE(client->get_nickname()));
        return;
    }

    client->set_nickname(nickname);
    client->welcome();
}
