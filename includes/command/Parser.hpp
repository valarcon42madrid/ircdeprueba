/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:31:16 by valarcon          #+#    #+#             */
/*   Updated: 2023/07/27 10:31:26 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IRC_PARSER_HPP
#define IRC_PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>

#include <vector>
#include <map>

class Parser;

#include "Command.hpp"

class Parser
{
    private:

        Server*                             _srv;
        std::map<std::string, Command *>    _commands;

        std::string     trim(const std::string& str);

    public:

        Parser(Server* srv);
        ~Parser();

        void    invoke(Client* client, const std::string& message);
};

#endif
