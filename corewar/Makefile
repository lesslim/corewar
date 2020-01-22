# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 15:29:42 by jrobin-h          #+#    #+#              #
#    Updated: 2019/12/08 13:01:42 by jrobin-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra

INCLUDES_DIR = includes/
SRCS_DIR = srcs/
BUILD_DIR = build/
LIB_DIR = ../libft/

vpath %.h $(INCLUDES_DIR)
vpath %.c $(SRCS_DIR)
vpath %.o $(BUILD_DIR)

INCLUDES = corewar.h \
	op.h

SRCS = arena.c \
	args.c \
	carr.c \
	command1.c \
	command10.c \
	command5.c \
	dead.c \
	free.c \
	game.c \
	game2.c \
	main.c \
	order.c \
	parse.c \
	print.c \
	reader.c \
	sort.c \
	true_op.c \
	vis2.c \
	vis_tools.c \
	visualize.c \
	work_with_winds.c

OBJS = $(SRCS:.c=.o)

.PHONY: all
all: check_build_dir build_lib $(NAME)

.PHONY: check_build_dir
check_build_dir:
	@if [ ! -d $(BUILD_DIR) ] ; then \
	mkdir $(BUILD_DIR); \
	fi

.PHONY: build_lib
build_lib:
	make -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIB_DIR)libft.a
	$(CC) $(addprefix $(BUILD_DIR), $(OBJS)) -L$(LIB_DIR) -lft -lncurses -o $(NAME)

$(OBJS): %.o : %.c $(INCLUDES)
	$(CC) -c $(CFLAGS) \
	-I$(INCLUDES_DIR) -I$(LIB_DIR)includes \
	$< -o $(BUILD_DIR)$@

.PHONY: clean_this
clean_this:
	rm -rf $(BUILD_DIR)

.PHONY: clean
clean: clean_this
	make -C $(LIB_DIR) clean

.PHONY: fclean_this
fclean_this: clean_this
	rm -f $(NAME)

.PHONY: fclean
fclean: fclean_this
	make -C $(LIB_DIR) fclean

.PHONY: re
re: fclean all
