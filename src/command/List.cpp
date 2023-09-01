#include "command/Command.hpp"

List::List(Server* srv) : Command(srv) {}

List::~List() {}

///iincluir SINTAX

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
			client->reply(RPL_LIST(client->get_nickname(), _srv->get_channels(i)->get_name()));
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
			client->reply(RPL_LIST(client->get_nickname(), _srv->get_channel(args[i])->get_name()));
					i++;
			///FALTA IMPLEMENTAR TOPIC Y CAMBIAR EN RPL_REPLY EL clientnickname POR _srv->get_channel(args[0])->get_topic()
		}
		if (i == 0)
			client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), args[i]));
	}
	return ;
}
