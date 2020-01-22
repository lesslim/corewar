# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 15:29:42 by jrobin-h          #+#    #+#              #
#    Updated: 2019/12/08 13:45:00 by jrobin-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

BIN_DIR = bin/

.PHONY: check_bin_dir
check_bin_dir:
	@if [ ! -d $(BIN_DIR) ] ; then \
	mkdir $(BIN_DIR); \
	fi

.PHONY: asm
asm:
	make -C asm

.PHONY: corewar
corewar:
	make -C corewar

$(BIN_DIR)asm: asm
	ln -fs "$(CURDIR)/asm/asm" $(BIN_DIR)

$(BIN_DIR)corewar: corewar
	ln -fs "$(CURDIR)/corewar/corewar" $(BIN_DIR)

.PHONY: all
all: check_bin_dir $(BIN_DIR)asm $(BIN_DIR)corewar

.PHONY: clean
clean:
	make -C asm clean
	make -C corewar clean_this

.PHONY: fclean
fclean:
	make -C asm fclean
	make -C corewar fclean_this
	rm -rf $(BIN_DIR)

.PHONY: re
re: fclean all
