# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adubedat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/23 17:07:31 by adubedat          #+#    #+#              #
#    Updated: 2018/03/06 17:32:10 by adubedat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = avm

SRC_PATH = $(ROOT)/src
ROOT = .
OBJ_FOLDER = obj
INC_PATH = $(ROOT)/includes

OBJ_PATH = $(OBJ_FOLDER)
DST_PATH = $(ROOT)
LFT_PATH =

CC = clang++ -g
CFLAGS = -std=c++11 -fsanitize=address#-Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I ,$(INC_PATH))
LDFLAGS = -fsanitize=address
LDLIBS =

SRC_NAME =	main.cpp \
			InputSource.cpp \
			AbstractVM.cpp \
			Lexer.cpp \
			Parser.cpp \
			Token.cpp \
			Instruction.cpp 

OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
DST = $(addprefix $(DST_PATH)/,$(NAME))

all: $(DST)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	printf "\e[32m[✔]\e[36m $@"
	printf "\033[0m\n"

$(DST): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(DST)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

clean:
	printf "\e[36m"
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

fclean: clean
	printf "\e[36m"
	@rm -fv $(DST)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

ac: all clean

norme:
	norminette $(SRC)

.PHONY: all clean fclean re
