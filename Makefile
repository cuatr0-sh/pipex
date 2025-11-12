# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 06:50:09 by asoria            #+#    #+#              #
#    Updated: 2025/11/10 07:22:19 by asoria           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror -Iincludes -Ilibft -g3

SRC_DIR		:= src
SRC_FILES	:= $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR		:= obj
OBJ_FILES	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBFT_DIR	:= includes/libft
LIBFT		:= $(LIBFT_DIR)/libft.a

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re: clean all

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo -e "\033[32m[✔] Built $(NAME)\033[0m"

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re
