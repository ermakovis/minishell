# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcase <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 11:31:10 by tcase             #+#    #+#              #
#    Updated: 2019/07/07 17:11:33 by tcase            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

CC=gcc
FLAGS= -Wall -Werror -Wextra

SRC_DIR=./src
LIB_DIR=./libft
OBJ_DIR=./obj

HEADER=./includes/$(NAME).h
SRC_NAME=main.c\
	init.c\
	init_env.c\
	init_bins.c\
	read_line.c\
	rl_input_manipulation.c\
	parser.c\
	pr_expans.c\
	pr_quotes.c\
	launch_programm.c\
	find_executable.c\
	msh_small_funcs.c\
	utils.c\
	cleanup.c

OBJ_NAME=$(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_NAME))

INC = -I ./includes -I $(LIB_DIR)/includes

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@make -s -C $(LIB_DIR)
	@$(CC) -o $(NAME) $(OBJ) $(LIB_DIR)/libft.a $(INC) -lcurses

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj
	@$(CC) -o $@ -c $< $(INC)
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

clean:
		@make clean -s -C $(LIB_DIR)
		@rm -f $(OBJ)

fclean: clean
		@make fclean -s -C $(LIB_DIR)
		@rm -rf *test*
		@rm -rf $(NAME)*

re:	fclean all

.PHONY: all, clean, fclean, re
