/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:34:04 by valarcon          #+#    #+#             */
/*   Updated: 2023/09/04 19:22:20 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_RESPONSE_HPP
#define IRC_RESPONSE_HPP

#include <iostream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <time.h>

#define ERR_NOTREGISTERED(source)                       "451 " + source + " :You have not registered"
#define ERR_ALREADYREGISTERED(source)                   "462 " + source + " :You may not register"
#define ERR_PASSWDMISMATCH(source)                      "464 " + source + " :Password is incorrect"
#define ERR_NONICKNAMEGIVEN(source)                     "431 " + source + " :Nickname not given"
#define ERR_NICKNAMEINUSE(source)                       "433 " + source + " " + source  + " :Nickname is already in use"

#define ERR_UNKNOWNCOMMAND(source, command)             "421 " + source + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(source, command)             "461 " + source + " " + command + " :Not enough parameters"

#define ERR_TOOMANYCHANNELS(source, channel)            "405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(source, channel)              "403 " + source + " " + channel + " :No such channel"
#define ERR_FORBIDDEN()              					"403  :Cannot ban an operator"
#define ERR_BADCHANNELKEY(source, channel)              "475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(source, channel)              "471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_ALREADYINVITED(source, target, channel)     "472 " + source + " :User " + target + " is already invited to channel " + channel
#define ERR_INVITEONLYCHAN(source, channel)             "473 " + source + " :Channel " + channel + " is invite only"
#define ERR_ALREADYONCHANNEL(source, channel)           "475 " + source + " :You are already on channel " + channel

#define ERR_CANNOTSENDTOCHAN(source, channel)           "404 " + source + " " + channel + " :Cannot send to channel"
#define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " " + channel + " :You're not channel operator"
#define ERR_NOPRIVILEGES(source, channel)           	"481 " + source + " " + channel + " :Permission Denied: Insufficient privileges"
#define ERR_BANNEDFROMCHAN(source, channel)   			"474 " + source + " " + channel + " :Cannot join channel, you are banned"
#define ERR_BANEDFROMCHAN(channel, target)              "473 :User " + target + " is banned from channel " + channel

#define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"

#define RPL_LIST(source, channel)						"319 " + source + " : " +  channel
#define RPL_INVITELIST(source, channel)                 "332 " + source + " : You are now on the waiting list for " +  channel
#define RPL_INVITE(source, channel, target)             "341 " + source + " " + channel + " : You are invited to channel " +  channel + " by " + target
#define RPL_WELCOME(source)                             "001 " + source + " :Welcome " + source + " to the ft_irc network"
#define NOTICE(source, channel, target)                 "001 " + source + " :Invitation to " + channel + " sent to " + target
#define RPL_NAMREPLY(source, channel, users)            "353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " " + channel + " :End of /NAMES list."


#define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel
#define RPL_PART(source, channel)                       ":" + source + " PART :" + channel
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message)                       ":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason
#define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE " + channel + " " + modes + " " + args


static inline void log(const std::string& message) 
{
    time_t      rawtime;
    struct tm   *timeinfo;
    char        buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    std::string str(buffer);

    (void)message;
    std::cout << "\033[0;34m[" << str << "]\033[0m ";
    std::cout << message << std::endl;
}

#endif
