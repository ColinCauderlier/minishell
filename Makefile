# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 11:38:44 by lucinguy          #+#    #+#              #
#    Updated: 2026/04/29 15:59:49 by ccauderl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
FLAGS		:= -lreadline
RM			:= rm -f
INCS		:= -I ./includes -I ./libft -I ./libft/ft_printf -I ./libft/gnl
LIBFT_DIR	:= libft
SRCS_DIR	:= src
OBJS_DIR	:= objs
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a

SRCS		:= 	tokenizer/tokenize.c \
			tokenizer/ft_isspace.c \
			tokenizer/get_content.c \
			tokenizer/free_lst.c \
			tokenizer/expander.c \
			tokenizer/get_new_content.c \
			tokenizer/temp.c \
			built-in/pwd/pwd.c \
			built-in/cd/cd.c \
			main.c

SRCS_FILES	:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		:= $(SRCS_FILES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(FLAGS) $(INCS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
