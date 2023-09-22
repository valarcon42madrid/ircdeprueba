NAME = ircserv

SRCS = src/main.cpp src/command/Command.cpp src/command/Invite.cpp src/command/Join.cpp src/command/Kick.cpp src/command/List.cpp src/command/Mode.cpp src/command/Nick.cpp src/command/Notice.cpp src/command/Parser.cpp src/command/Part.cpp src/command/Pass.cpp src/command/Ping.cpp src/command/Pong.cpp src/command/PrivMsg.cpp src/command/Quit.cpp src/command/User.cpp src/network/Channel.cpp src/network/Client.cpp src/network/Server.cpp

OBJS = $(SRCS:.cpp=.o)

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -I ./includes

RM = rm -rf


.cpp.o:
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n"
	@echo "\033[0;32mCompiling IRC server..."
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "Done!\033[0m"

clean:
	@echo "\033[0;31mRemoving binaries..."
	@$(RM) $(OBJS)
	@echo "Done!\n\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	@$(RM) $(NAME)
	@echo "Done!\n\033[0m"

re: fclean all

.PHONY: all clean, fclean, re
