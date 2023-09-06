PRUEBA DE OTRO CLIENTE IRC (WEECHAT):

 ABRIR WEECHAT CON DOCKER
 
 docker run -ti weechat/weechat

 EN TERMINAL CONSULTAR LA IP QUE EMPLEA DOCKER:
 
 ifconfig | grep inet
 
 (*y copiamos 1º inet despues de las inet6, una con netmask y brodcast a continuación)
 (TAMBIEN SE PUEDE EMPLEAR host.docker.internal)
 
 EN WEECHAT: 
 
 AÑADIR SERVIDOR:
 
/server add CUALQUIERNOMBRE (I.P.consultada)/6667 -tls

IMPORTANTE:

se desactiva el tls:
/set irc.server_default.tls off

Se introduce el password:
/set irc.server.CUALQUIERNOMBRE.password (PASSWORDPUESTAEN./IRCSERV_6667_AQUI)

CONFIGURAR AL GUSTO:

/set irc.server.libera.username "My user name"

/set irc.server.libera.realname "My real name"
...

CONECTARSE: 
/connect CUALQUIERNOMBRE

/join "GRUPO"

PARA HABLAR A ALGUIEN/ALGO:
/query TARGET mensaje


-----------------------------------------------


¿CÓMO USAR EL EJECUTABLE?:

Trás hacer make ejecute en terminal:

./ircserv 6667 Password

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

PASS Password


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

 . LIST
Muestra los canales y sus topics, se usa:

"LIST"     (PARA TODOS LOS CANALES)
"LIST channel channel channel" (PARA CANALES CONCRETOS)

_______________________________________________
POR ULTIMO CABE DESTACAR:

-> EL COMANDO MODE, EMPLEADO PARA FIJAR O ELIMINAR OPCIONES DE UN OBJETIVO 

MODE canal +/-Flag "TARGETifNEEDED"

 K pone key en un canal ("MODE micanal +k contraseña" hace que para acceder debas hacer "JOIN micanal contraseña") 
     L  establece el limite de clientes   
    N  deshabilita los mensajes externos (es decir +n evita los NOTICE al canal)               
    "+b" banea a un client 
    , "+t TOPCO" crea un topic en el canal
    , "+i" hace que solo se pueda acceder mediante la recepción de un invite
    
MODE channel flags (user/args)

EJ: MODE 6667 +b usuario


-> INVITE Channel Nickname
(Relevante para salas con +i)

-> PART

Abandona el/los canales especificados

syntax: PART channels "message-optional"


-> KICK

echar a alguien

syntax: KICK channel client "message-optional"

KICK 6667 v : expulsado

-> QUIT

 (...)
