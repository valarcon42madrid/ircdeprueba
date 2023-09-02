/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:36:41 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/02 11:15:09 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

Mode::Mode(Server* srv) : Command(srv) {}

Mode::~Mode() {}


void    Mode::execute(Client* client, std::vector<std::string> args)
{

    if (args.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "MODE"));
        return;
    }
    
    std::string target = args.at(0);
    
    Channel *channel = _srv->get_channel(target);

    if (!channel)
    {
		/*if (target.size())
		{
					std::cout << "mode changed for " << target << std::endl;
					return ;
	
		}*/
        client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), target));
        return;
    }

    if (channel->get_admin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), target));
        return;
    }

	int i = 0, p = 2;
	char c;
    
    while ((c = args[1][i]))
    {
        char prev_c = i > 0 ? args[1][i - 1] : '\0';
        bool active = prev_c == '+';

        switch (c) 
        {
            case 'n':
            {
                channel->set_ext_msg(active);
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+n" : "-n"), ""));
                break;
            }
			case 'l':
            {
                channel->set_limit(active ? atoi(args[p].c_str()) : 0);
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+l" : "-l"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
			case 'k':
            {
                channel->set_key(active ? args[p] : "");
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+k" : "-k"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
			 case 't':
            {
                channel->set_topic(active ? args[p] : "");
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+t" : "-t"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
            default:
            break;
        }
        i++;
    }
}
