#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/09/01 12:23:36 by ale-batt          #+#    #+#             *#
#*   Updated: 2016/11/02 15:46:35 by ale-batt         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

CMOCKA_DIR = cmocka
CMOCKA_BUILD = $(CMOCKA_DIR)/build
CMOCKA_LIB = $(CMOCKA_BUILD)/src/libcmocka.a

TEST_DIR = $(shell find ./* -type d -maxdepth 0 -not -path "./cmocka" )
TEST_FILE = $(shell find $(TEST_DIR) -type f)

A_OUT = $(addsuffix /a.out, $(TEST_DIR))

CC = gcc
LIBFT_DIR = ..
LIBS = $(LIBFT_DIR)/libft.a $(CMOCKA_LIB)
INCLUDES = -I$(LIBFT_DIR)/includes -I$(CMOCKA_DIR)/include

.PHONY: all clean fclean re test
	
all:	$(CMOCKA_LIB) $(LIBFT_DIR)/libft.a $(A_OUT) test

#%/a.out: %/test.c
%/a.out: %/*.c
	$(CC) $(INCLUDES) -o $@ $^ $(LIBS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(CMOCKA_BUILD):
	@git submodule init
	@git submodule update

$(CMOCKA_LIB): $(CMOCKA_BUILD)
	@mkdir -p $(CMOCKA_BUILD) && cd $(CMOCKA_BUILD) && cmake .. -DWITH_STATIC_LIB=on && make

clean:
	@rm -rf $(A_OUT)

fclean: clean
	@rm -rf cmocka

re: fclean all

.SILENT: 
test:
	for EXEC in $(A_OUT);	\
	do						\
		$$EXEC;				\
		echo "-----";		\
	done					\
