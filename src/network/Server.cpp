/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama <sasalama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:42:20 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/18 13:58:43 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "network/Server.hpp"


Server::Server(const std::string &port, const std::string &pass) 
    : _host("127.0.0.1"), _port(port), _pass(pass)
{
    _running = 1;
    _sock = create_socket();
    _parser = new Parser(this);
}

Server::~Server() 
{
    delete _parser;

	_clients.clear();

	for (client_iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		delete it->second;
	}
	_channels.clear();
	for (channel_iterator it_channel = _channels.begin(); it_channel != _channels.end(); it_channel++)
	{
		(*it_channel)->finish();
		delete *it_channel;
	}
	_pfds.clear();
}

void signalHandler(int signum) 
{
    (void)signum;
    exit(0);
}


void            Server::start()
{

    pollfd srv = {_sock, POLLIN, 0};
    _pfds.push_back(srv);

    log("Server is listening...");

    while (_running)
    {
        if (poll(_pfds.begin().base(), _pfds.size(), -1) < 0)
            throw std::runtime_error("Error while polling from fd!");

        signal(SIGINT, signalHandler);
        for (pfd_iterator it = _pfds.begin(); it != _pfds.end(); it++)
        {
            if (it->revents == 0)
                continue;
            if ((it->revents & POLLHUP) == POLLHUP)
            {
                this->on_client_disconnect(it->fd);
                break;
            }
            if ((it->revents & POLLIN) == POLLIN)
            {
                if (it->fd == _sock)
                {
                    this->on_client_connect();
                    break;
                }

                this->on_client_message(it->fd);
            }
        }
    }
}


std::string     Server::get_password() const 
{
    return _pass;
}

Client*         Server::get_client(const std::string& nickname)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        if (!nickname.compare(it_b->second->get_nickname()))
            return it_b->second;

        it_b++;
    }

    return NULL;
}

Channel*        Server::get_channel(const std::string& name)
{
	for (channel_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (it.operator*()->get_name() == name)
			return it.operator*();

	return NULL;
}

Channel*        Server::get_channels(int i)
{
	int x = 0;
	for (channel_iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (x == i)
			return it.operator*();
		x++;
	}
	return NULL;
}

std::string gethostname(const sockaddr_in& addr) {
    struct hostent* host = gethostbyaddr((char*)&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);
    if (host == NULL) {
        return "";
    }
    return host->h_name;
}

void            Server::on_client_connect()
{

    int         fd;
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);

    fd = accept(_sock, (sockaddr *) &addr, &size);
    if (fd < 0)
        throw std::runtime_error("Error while accepting a new client!");

    pollfd  pfd = {fd, POLLIN, 0};
    _pfds.push_back(pfd);

    std::string hostname = gethostname(addr);
    if (hostname == "")
        throw std::runtime_error("Error while getting a hostname on a new client!");

    Client* client = new Client(fd, ntohs(addr.sin_port), hostname);
    _clients.insert(std::make_pair(fd, client));

    log(client->get_hostname().c_str() + (std::string)":" + std::to_string(client->get_port()) + (std::string)" has connected.");
}

void            Server::on_client_disconnect(int fd)
{
    try
    {
        Client* client = _clients.at(fd);

        client->leave();

        log(client->get_hostname().c_str() + (std::string)":" + std::to_string(client->get_port()) + (std::string)" has disconnected.");

        _clients.erase(fd);

        pfd_iterator it_b = _pfds.begin();
        pfd_iterator it_e = _pfds.end();

        while (it_b != it_e)
        {
            if (it_b->fd == fd)
            {
                close(fd);
                break;
            }

            it_b++;
        }

        delete client;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error while disconnecting! " << e.what() << std::endl;
    }
}

void            Server::on_client_message(int fd)
{
    try
    {
        Client*     client = _clients.at(fd);
        std::string message = this->read_message(fd, client);
       if (message != "") 
        	_parser->invoke(client, message);
    }
    catch (const std::exception& e) 
    {
        std::cout << "Error while handling the client message! " << e.what() << std::endl;
    }
}

std::string     Server::read_message(int fd, Client *client)
{
	client->buffer_clear();
    while (true)
    {
        char c;

        if ((recv(fd, &c, 1, 0) < 0))
            throw std::runtime_error("Error while reading buffer from a client!");
        if (c == '\n')
            break;
        client->add_buffer(c);
		 if (c != '\n')
            return "";
    }
	client->buff_ready();
    return client->get_buffer();
}

Channel*        Server::create_channel(const std::string& name, const std::string& key, const std::string& topic, Client* client)
{
    Channel *channel = new Channel(name, key, topic, client);
    _channels.push_back(channel);

    return channel;
}

int             Server::create_socket()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
        throw std::runtime_error("Error while opening a socket!");

    int optval = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        throw std::runtime_error("Error while setting socket options!");

    if (fcntl(sock_fd, F_SETFL, O_NONBLOCK))
        throw std::runtime_error("Error while setting socket to NON-BLOCKING!");

    struct sockaddr_in  serv_addr = {};

    std::memset((char*) &serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(_port.c_str()));

    if (bind(sock_fd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        throw std::runtime_error("Error while binding a socket!");

    if (listen(sock_fd, MAX_CONNECTIONS) < 0)
        throw std::runtime_error("Error while listening on a socket!");

    return sock_fd;
}
