# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 19:47:08 by gdelabro          #+#    #+#              #
#    Updated: 2020/10/26 18:42:08 by gdelabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping

SRC_PATH = src
SRC_NAME = main.c time_functions.c get_ipv4.c parser.c ping.c stat.c

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = gcc
CFLAGS = #-Wall -Werror -Wextra

LIB = ft_printf/libftprintf.a

SRC = $(addprefix $(SRC_PATH)/,$(SR_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(LIB) $(NAME)

$(LIB):
	@make -C ft_printf

$(NAME): $(OBJ)
	@printf "\n"
	@$(CC) $^ $(LIB) -o $@
	@echo "Compilation of \033[33;1m$(NAME)\033[0;1m: [\033[1;32mOK\033[0;1m]"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@printf "\033[34;1m| \033[0;1m"
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C ft_printf clean
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "\033[33;1m$(NAME)\033[0;1m: objects deleted"

fclean: clean
	@make -C ft_printf fclean
	@rm -rf $(NAME)
	@echo "\033[33;1m$(NAME)\033[0;1m: $(NAME) deleted"

re: fclean all

.PHONY: all clean fclean re
