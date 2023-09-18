/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:32:59 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/18 13:58:41 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <sys/socket.h>
#include <sys/poll.h>

#include <string>
#include <vector>

class Client;

#include "Channel.hpp"
#include "response.hpp"


enum ClientState
{
    HANDSHAKE,
    LOGIN,
    REGISTERED,
    DISCONNECTED
};


class Client 
{
    private:
        
        int             _fd;
        int             _port;

        std::string     _nickname;
        std::string     _username;
        std::string     _realname;
        std::string     _hostname;
		std::string     _buffer;
		bool			_fb;

        ClientState     _state;
        Channel*        _channel;

        Client();
        Client(const Client &src);

    public:

        Client(int fd, int port, const std::string &hostname);
        ~Client();

        int             get_fd() const;
        int             get_port() const;

        std::string     get_nickname() const;
        std::string     get_username() const;
        std::string     get_realname() const;
        std::string     get_hostname() const;
        std::string     get_prefix() const;
		std::string     get_buffer();

        void            buffer_clear();

		void			buff_ready();

		void            add_buffer(char c);

        Channel*        get_channel() const;

        void            set_nickname(const std::string &nickname);
        void            set_username(const std::string &username);
        void            set_realname(const std::string &realname);
        void            set_state(ClientState state);
        void            set_channel(Channel *channel);

        bool            is_registered() const;

        void            write(const std::string& message) const;
        void            reply(const std::string& reply);

        void            welcome();

        void            join(Channel *channel);
        void            leave();
};

#endif
