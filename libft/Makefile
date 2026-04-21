# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 16:49:33 by lucinguy          #+#    #+#              #
#    Updated: 2026/03/06 16:35:41 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := libft.a
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
AR          := ar rcs
RM          := rm -f

INCS        := -I . -I ./ft_printf -I ./gnl

# --------------------------- Mandatory ---------------------------- #

# ------ Libft sources ------ #
SRCS := \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	\
	ft_itoa.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strmapi.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_strstr.c

# ------ ft_printf sources ------ #
PRINTF_SRCS := \
	ft_printf/ft_printf.c \
	ft_printf/ft_printf_utils.c \
	ft_printf/conv.c \
	ft_printf/checktype.c

# ------ gnl sources ------ #
GNL_SRCS := \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c

# ------------------------------- Bonus ------------------------------ #

BSRCS := \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c

OBJS  := $(SRCS:.c=.o) $(PRINTF_SRCS:.c=.o) $(GNL_SRCS:.c=.o)
BOBJS := $(BSRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(NAME) $(BOBJS)
	$(AR) $(NAME) $(BOBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
