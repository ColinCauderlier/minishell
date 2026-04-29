# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/29 18:15:00 by lucinguy          #+#    #+#              #
#    Updated: 2026/04/29 19:11:10 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -f
OBJS_DIR	:= objs
LIBFT_DIR	:= ../../libft
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a
INCS		:= -I . -I ../../libft -I ../../libft/ft_printf -I ../../libft/ft_fprintf -I ../../libft/gnl

SRCS		:= commands.c \
				error_management.c \
				main.c \
				path.c \
				utils.c \
				utils2.c

OBJS		:= $(SRCS:%.c=$(OBJS_DIR)/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(OBJS_DIR)/%.o: %.c pipex.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
