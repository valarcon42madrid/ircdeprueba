ANTES DE PROFUNDIZAR EN EL CÓDIGO ES CONVENIENTE ACLARAR ALGUNOS PARÁMETROS Y CONCEPTOS SENCILLOS:

En RESPONSE

AQUI TENEMOS LOS ERRORES Y RESPUESTAS QUE EMPLEA EL PROGRAMA.

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

#define ERR_BADCHANNELKEY(source, channel)              "475 " + source + " " + channel + " :Cannot join channel (+k)"

#define ERR_CHANNELISFULL(source, channel)              "471 " + source + " " + channel + " :Cannot join channel (+l)"

#define ERR_CANNOTSENDTOCHAN(source, channel)           "404 " + source + " " + channel + " :Cannot send to channel"

#define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " " + channel + " :You're not channel operator"


#define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick/channel"

#define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"



#define RPL_WELCOME(source)                             "001 " + source + " :Welcome " + source + " to the ft_irc network"

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


A CONTINUACION SE OBSERVA UN STATIC (no accesible por otras funciones) INLINE (unida por definición a otra funciòn; ergo sin una dirección de memoria propia). ESTA SE EMPLEARÁ EN CUALQUIER ERR_ y RPL_ DEL GRUPO DEFINIDO ANTERIORMENTE.

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

---------------------------------------------------------

En CLIENT

 EL CLIENTE TIENE 4 ESTADOS POSIBLES:

 enum ClientState
{
    HANDSHAKE,
    LOGIN,
    REGISTERED,
    DISCONNECTED
};

------------------------------------------------
En SERVER 

POR AHORA TENEMOS 999 COMO MÁXIMO DE CONEXIONES

#define MAX_CONNECTIONS 999
_______________________________________________________________

¿CÓMO USAR EL EJECUTABLE?:

Trás hacer make ejecute en terminal:

./ircserv 6667 127.0.0.1

Ésto iniciará el servidor y permitirá a los usuarios unirse.


Desde otra terminal y sin finalizar la ejecución anterior podremos unirnos e identificarnos mediante los comandos:


·  NC

netcat permite leer y escribir datos entre dos redes.

nc -c 127.0.0.1 6667



·  NICK

para definir tu nick o apodo:

NICK v



·  PASS

para unirse/logearse

PASS 127.0.0.1


·  USER

define las características del usuario

USER valarcon 6667 127.0.0.1 victor


· JOIN

para unirse al canal

JOIN 6667


FINALMENTE PODREMOS EMPLEAR COMANDOS PARA COMUNICARNOS COMO:

· PING

Prueba simple que solo tiene función fática (o de medida del tiempo que tardan en viajar los paquetes de datos).


· PRIVMSG

Mensaje privado a un usuario


· NOTICE

Mensaje a un objetivo (canal o usuario)

_______________________________________________
POR ULTIMO CABE DESTACAR:

-> EL COMANDO MODE, EMPLEADO PARA FIJAR O ELIMINAR OPCIONES DE UN OBJETIVO (canal o usuario). Son “i”, “o”(capaz de kickear/admin) para usuarios y “b”, “k”, “m”, “o”, “p”, “s”, “t”, “v” para canales.

MODE channel(/nickname aun no implementado) flags (user/args)

MODE 6667 +l

-> PART

Abandona el/los canales especificados

syntax: PART channels message


-> KICK

echar a alguien

syntax: KICK channel client :message

-> QUIT

 (...)
