# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/29 18:15:00 by lucinguy          #+#    #+#              #
#    Updated: 2026/04/29 18:06:50 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libftfprintf.a
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar rcs
RM			:= rm -f
INCS		:= -I .

SRCS		:= \
	ft_fprintf.c \
	ft_fprintf_utils.c \
	conv.c \
	checktype.c

OBJS		:= $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all