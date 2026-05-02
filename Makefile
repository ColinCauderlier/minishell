# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 11:38:44 by lucinguy          #+#    #+#              #
#    Updated: 2026/05/02 16:19:22 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
PIPEX_NAME	:= pipex
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
FLAGS		:= -lreadline
RM			:= rm -f
INCS		:= -I ./includes -I ./libft -I ./libft/ft_printf -I ./libft/ft_fprintf -I ./libft/gnl
LIBFT_DIR	:= libft
PIPEX_DIR	:= src/pipex
SRCS_DIR	:= src
OBJS_DIR	:= objs/minishell
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a

SRCS		:= 	tokenizer/tokenize.c \
			tokenizer/ft_isspace.c \
			tokenizer/get_content.c \
			tokenizer/free_lst.c \
			tokenizer/expander.c \
			tokenizer/get_new_content.c \
			tokenizer/temp.c \
			envp_management/envp.c \
			envp_management/envp_utils.c \
			built-in/pwd/pwd.c \
			built-in/cd/cd.c \
			main.c

SRCS_FILES	:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		:= $(SRCS_FILES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(LIBFT_LIB) $(NAME) $(PIPEX_NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(FLAGS) $(INCS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(PIPEX_NAME): $(LIBFT_LIB)
	$(MAKE) -C $(PIPEX_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR) objs/built-in objs/tokenizer objs/main.o objs/pipex
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PIPEX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(PIPEX_NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PIPEX_DIR)

re: fclean all

.PHONY: all clean fclean re
