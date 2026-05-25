# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 11:38:44 by lucinguy          #+#    #+#              #
#    Updated: 2026/05/25 19:27:32 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
FLAGS		:= -lreadline
RM			:= rm -f
INCS		:= -I ./includes -I ./libft -I ./libft/ft_printf -I ./libft/ft_fprintf -I ./libft/gnl
LIBFT_DIR	:= libft
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
			exec/exec.c \
			exec/init_exec.c \
			exec/builtin_exec.c \
			exec/path.c \
			exec/free.c \
			exec/free_pipes_and_pids.c \
			exec/syntax.c \
			exec/commands.c \
			built-in/pwd/pwd.c \
			built-in/cd/cd.c \
			built-in/export/export.c \
			built-in/export/export_parse.c \
			built-in/export/export_print.c \
			built-in/env/env.c \
			built-in/exit/exit.c \
			built-in/echo/echo.c \
			envp_management/envp.c \
			envp_management/update_envp.c \
			envp_management/sort_envp.c \
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
	$(RM) -r $(OBJS_DIR) objs/built-in objs/tokenizer objs/main.o objs/pipex
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(PIPEX_NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
