# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 15:29:42 by jrobin-h          #+#    #+#              #
#    Updated: 2019/10/23 15:29:44 by jrobin-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INCLUDES_DIR = includes/
SRCS_DIR = srcs/
BUILD_DIR = build/
LIB_DIR = ../libft/

vpath %.h $(INCLUDES_DIR)
vpath %.c $(SRCS_DIR)
vpath %.o $(BUILD_DIR)

INCLUDES = asm.h \
	g_op.h \
	op.h \
	regex_op.h

SRCS = io/write_swap_endian.c \
	io/read_file.c \
	io/write_n_bytes.c \
	io/write_unsigned_int.c \
	io/write_bytecode.c \
	io/output.c \
	analyze/get_coding_byte.c \
	analyze/analyzer_name_and_comment.c \
	analyze/write_args.c \
	analyze/is_argument.c \
	analyze/write_argument_type.c \
	analyze/analyzer_op.c \
	analyze/analyze.c \
	analyze/fill_file_data.c \
	analyze/ft_ltoi_safe.c \
	main/g_op.c \
	main/process_file.c \
	main/main.c \
	main/tokenize.c \
	data_handlers/del_clear_token.c \
	data_handlers/del_regexes.c \
	data_handlers/compile_regexes.c \
	helpers/append_to_list.c

OBJS = $(SRCS:.c=.o)

.PHONY: all
all: check_build_dir build_lib $(NAME)

.PHONY: check_build_dir
check_build_dir:
	@if [ ! -d $(BUILD_DIR) ] ; then \
	mkdir $(BUILD_DIR); \
	mkdir $(BUILD_DIR)io; \
	mkdir $(BUILD_DIR)analyze; \
	mkdir $(BUILD_DIR)main; \
	mkdir $(BUILD_DIR)data_handlers; \
	mkdir $(BUILD_DIR)helpers; \
	fi

.PHONY: build_lib
build_lib:
	make -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIB_DIR)libft.a
	$(CC) $(addprefix $(BUILD_DIR), $(OBJS)) -L$(LIB_DIR) -lft -o $(NAME)

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
