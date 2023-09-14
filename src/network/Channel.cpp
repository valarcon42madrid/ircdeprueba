/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:40:23 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/14 09:59:23 by sasalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/Channel.hpp"


Channel::Channel(const std::string& name, const std::string& key, const std::string& topic, Client* admin)
    : _name(name), _admin(admin), _k(key), _t(topic), _l(0), _n(false), _i(false)
{

}

Channel::~Channel() {}


std::string                 Channel::get_name() const { return _name; }
Client*                     Channel::get_admin() const { return _admin; }

std::string                 Channel::get_key() const { return _k; }
std::string                 Channel::get_topic() const { return _t; }
size_t                      Channel::get_limit() const { return _l; }
bool                        Channel::ext_msg() const { return _n; }

size_t                      Channel::get_size()const { return _clients.size(); }

std::vector<std::string>    Channel::get_nicknames()
{
    std::vector<std::string> nicknames;

    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        Client* client = *it_b;

        std::string nick = (client == _admin ? "@" : "") + client->get_nickname();
        nicknames.push_back(nick);

        it_b++;
    }

    return nicknames;
}


void                        Channel::set_key(std::string key) { _k = key; }
void                        Channel::set_topic(std::string topic) { _t = topic; }
void                        Channel::set_limit(size_t limit) { _l = limit; }
void                        Channel::set_ext_msg(bool flag) { _n = flag; }
void                        Channel::set_invite(bool flag) { _i = flag; }
bool						Channel::get_invite() const { return _i; }

void                        Channel::broadcast(const std::string& message)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        (*it_b)->write(message);
        it_b++;
    }
}

void                        Channel::broadcast(const std::string& message, Client* exclude)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        if (*it_b == exclude)
        {
            it_b++;
            continue;
        }

        (*it_b)->write(message);
        it_b++;
    }
}

void                        Channel::add_client(Client* client)
{
    _clients.push_back(client);
}

void                        Channel::remove_client(Client* client)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
            _clients.erase(it_b);
        
        it_b++;
    }

    client->set_channel(NULL);

    if (client == _admin)
    {
        _admin = *(_clients.begin());

        std::string message = client->get_nickname() + " is now the admin of the channel " + _name;
        log(message);
    }
}

bool                        Channel::is_ban_client(Client* client)
{
    client_iterator it_b = _banned.begin();
    client_iterator it_e = _banned.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
			return 1;

        it_b++;
    }
	return 0;
}

void						Channel::client_to_waitlist(Client* client)
{
	_waitlist.push_back(client);
}

bool						Channel::client_at_waitlist(Client* client)
{
	client_iterator it_b = _waitlist.begin();
    client_iterator it_e = _waitlist.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
			return (1);
        it_b++;
    }
	return (0);
}

void						Channel::client_out_waitlist(Client* client)
{
	client_iterator it_b = _waitlist.begin();
    client_iterator it_e = _waitlist.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
            _waitlist.erase(it_b);

        it_b++;
    }
}

void                        Channel::ban_client(Client* client)
{
	if (client != NULL)
        _banned.push_back(client);
}

void                        Channel::remove_bans(Client* client)
{
	Client *cl = client;
	if (cl != NULL)
	{
		client_iterator it_b = _banned.begin();
		client_iterator it_e = _banned.end();
   		 while (it_b != it_e)
   		 {
			  if (*it_b == client)
            	 _banned.erase(it_b);
        	it_b++;
        }
	}
	else
	{
		client_iterator it_b = _banned.begin();
    	client_iterator it_e = _banned.end();

    	while (it_b != it_e)
   		 {
        	_banned.erase(it_b);
       		 it_b++;
   		 }
	}

}

void                        Channel::kick(Client* client, Client* target, const std::string& reason)
{
    this->broadcast(RPL_KICK(client->get_prefix(), _name, target->get_nickname(), reason));
    this->remove_client(target);

    std::string message = client->get_nickname() + " kicked " + target->get_nickname() + " from channel " + _name;
    log(message);
}

void                        Channel::invite(Client* client, Client* target)
{
	  _invited.push_back(target);
	  target->reply(RPL_INVITE(target->get_nickname(), client->get_channel()->get_name(), client->get_nickname()));
	  client->reply(NOTICE(client->get_nickname(), client->get_channel()->get_name(), target->get_nickname()));

}

bool                        Channel::is_invited(Client* client)
{
    client_iterator it_b = _invited.begin();
    client_iterator it_e = _invited.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
            return (1);
        it_b++;
    }
    return (0);
}

void					Channel::finish()
{
	if (_admin)
		delete _admin;
	_clients.clear();
	_banned.clear();
	_waitlist.clear();
	_invited.clear();
}
