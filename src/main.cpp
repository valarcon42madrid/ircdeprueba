/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:42:37 by valarcon          #+#    #+#             */
/*   Updated: 2023/07/27 10:42:40 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        throw std::runtime_error("Usage: ./ircserv <port> <password>");
    
    Server  server(argv[1], argv[2]);

    try
    {
        server.start();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
