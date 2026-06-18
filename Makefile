# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 11:38:44 by lucinguy          #+#    #+#              #
#    Updated: 2026/06/18 17:10:00 by ccauderl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
FLAGS		:= -lreadline
RM			:= rm -rf
INCS		:= -I ./includes -I ./libft -I ./libft/ft_printf -I ./libft/ft_fprintf -I ./libft/gnl
LIBFT_DIR	:= libft
SRCS_DIR	:= src
OBJS_DIR	:= objs/minishell
LIBFT_LIB	:= $(LIBFT_DIR)/libft.a

.SILENT:

SRCS		:= 	tokenizer/tokenize.c \
			tokenizer/ft_isspace.c \
			tokenizer/get_content.c \
			tokenizer/free_lst.c \
			tokenizer/expander.c \
			tokenizer/expander_utils.c \
			tokenizer/get_new_content.c \
			exec/exec.c \
			exec/init_exec.c \
			exec/init_redir.c \
			exec/init_redirs_utils.c \
			exec/heredoc.c \
			exec/heredoc_utils.c \
			exec/builtin_exec.c \
			exec/path.c \
			exec/free.c \
			exec/free_pipes_and_pids.c \
			exec/single_command.c \
			exec/syntax.c \
			exec/commands.c \
			exec/get_commands.c \
			built-in/pwd/pwd.c \
			built-in/cd/cd.c \
			built-in/cd/cd_utils.c \
			built-in/export/export.c \
			built-in/export/export_parse.c \
			built-in/export/export_print.c \
			built-in/unset/unset.c \
			built-in/env/env.c \
			built-in/exit/exit.c \
			built-in/echo/echo.c \
			envp_management/envp.c \
			envp_management/update_envp.c \
			envp_management/sort_envp.c \
			envp_management/envp_utils.c \
			signal_management/signal_handler.c \
			main.c

SRCS_FILES	:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		:= $(SRCS_FILES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(FLAGS) $(INCS) $(OBJS) $(LIBFT_LIB) -o $(NAME)
	@echo "✓ $(NAME) compiled successfully!"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) -s clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -s fclean -C $(LIBFT_DIR)
	$(MAKE) -s fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
