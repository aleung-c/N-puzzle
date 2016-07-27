# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/19 13:34:29 by aleung-c          #+#    #+#              #
#    Updated: 2016/07/19 13:34:33 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Npuzzle

SRC = ./src/Main.cpp \
./src/Heuristic.cpp \
./src/InitPuzzle.cpp \
./src/PuzzleState.cpp \
./src/Point.cpp \
./src/Resolver.cpp \
./src/PStools.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
