/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:00:52 by sasalama          #+#    #+#             */
/*   Updated: 2023/09/14 10:00:54 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.hpp"

List::List(Server* srv) : Command(srv) {}

List::~List() {}

///SINTAX: LIST [optional specific channel (or channels with spaces between)] 

void    List::execute(Client* client, std::vector<std::string> args)
{
	int i = 0;
    if (args.empty())
    {
		Channel* ch = _srv->get_channels(i);
		if (!ch)
			return;
		while (ch)
		{
			client->reply(RPL_LIST(_srv->get_channels(i)->get_topic(), _srv->get_channels(i)->get_name()));
			i++;
			Channel* ch = _srv->get_channels(i);
			if (!ch)
				return;
		}
    }
	else
	{
		while (_srv->get_channel(args[i]))
		{
			client->reply(RPL_LIST(_srv->get_channels(i)->get_topic(), _srv->get_channels(i)->get_name()));
			i++;
		}
		if (i == 0)
			client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), args[i]));
	}
	return ;
}
