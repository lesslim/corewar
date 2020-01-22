# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/02 15:59:41 by jrobin-h          #+#    #+#              #
#    Updated: 2019/12/08 12:50:09 by jrobin-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.index

SRCS =	ft_printf.c						\
		parse.c							\
		parse_helpers.c 				\
		handle.c						\
		handle_char.c					\
		handle_helpers_common.c			\
		h_signed.c						\
		h_unsigned.c					\
		h_double.c						\
		bases.c							\
		binary_fraction_to_decimal.c	\
		get_mantissa_binary.c			\
		h_a_helpers.c					\
		get_mantissa_decimal.c			\
		handle_decimal_precision.c		\
		get_normal_notation.c			\
		h_gf_helpers.c					\
		big_handling.c					\
		big_multiplication.c			\
		big_addition.c					\
		big_concat.c

HEADS =	ft_printf_internal.h	\
		parse_helpers.h 		\
		bases.h					\
		libbig.h

OBJS = $(SRCS:.c=.o)

INCLUDES = ./includes/

LIBDIR = ../
LIBINCLUDES = $(LIBDIR)includes/
LIBHEADS = $(LIBINCLUDES)libft.h $(LIBINCLUDES)ft_printf.h

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3

all: $(NAME)

$(NAME): $(OBJS)
	echo $(OBJS) > $(NAME)

$(OBJS): %.o : %.c $(addprefix $(INCLUDES), $(HEADS)) $(LIBHEADS)
	$(CC) -c $(CFLAGS) -I $(INCLUDES) -I $(LIBINCLUDES) $<

clean:
	rm -f $(OBJS) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
