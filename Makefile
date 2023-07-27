NAME = ircserv

SRCS = $(wildcard src/*.cpp src/network/*.cpp src/command/*.cpp)

# wildcard is a pattern to use all names of any of the following matches #

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
