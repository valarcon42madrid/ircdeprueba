
./ft_irc 6667 127.0.0.1

nc -c 127.0.0.1 6667

Nick v

 PASS <password>    (((127.0.0.1))

 USER <username> <hostname> <servername> <realname>
(USER valarcon 6667 127.0.0.1 victor)

Join 6667


 PING <server1> [<server2>]

PRIVMSG <msgtarget> :<message>

NOTICE <msgtarget> <message>



The MODE command is used to set or remove options (or modes) from a given target. Our user modes : i, o. Our channels modes: b,k,m,o,p,s,t,v
   MODE <nickname> <flags> (user)
   MODE <channel> <flags> [<args>]
