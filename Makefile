# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/29 17:16:35 by tbruinem      #+#    #+#                  #
#    Updated: 2021/03/29 17:32:20 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = project
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INCL_DIR = ./incl/

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC =	list.c \
		memory.c \
		push_swap.c \
		stack.c

OBJ := $(SRC:%.c=$(OBJ_DIR)%.o)
SRC := $(SRC:%.c=$(SRC_DIR)%.c)

HEADERS = push_swap.h
HEADERS := $(HEADERS:%.h=$(INCL_DIR)%.h)

INCL_FOLDERS = $(dir $(HEADERS))
INCL_FOLDERS := $(sort $(INCL_FOLDERS))

INCL := $(addprefix -I ,$(INCL_FOLDERS))

test:
	echo $(SRC)
	echo $(OBJ)
	echo $(INCL)

all: $(NAME)
	@mkdir -p ./html/uploads

obj/%.o: src/%.c $(HEADER)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@

$(NAME): checker push_swap

.SECONDEXPANSION:
push_swap_OBJS := $(OBJ_DIR)push_swap.o $(OBJ)
checker_OBJS := $(OBJ_DIR)checker.o $(OBJ)

checker push_swap: $$($$@_OBJS)
	$(CC) $(CFLAGS) $(INCL) $^ -o $(@)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
