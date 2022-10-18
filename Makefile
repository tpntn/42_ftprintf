# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 10:24:54 by tpontine          #+#    #+#              #
#    Updated: 2022/10/18 17:48:41 by tpontine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
EXE := ft_printf

CC := gcc
CFLAGS := -c -Wall -Werror -Wextra
INCLUDES := -I./Libft -I./includes

SRC_DIR := ./src
OBJ_DIR := ./obj
SRCS := ./src/$(EXE).c \
	./src/ft_fto.c \
	./src/ft_itoas.c \
	./src/ft_puts.c \
	./src/ftoa_params.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIB_DIR := libft
LIBFT := $(addprefix $(LIB_DIR), libft.a)
LIB_OBJS = $(shell find $(LIB_DIR) -type f | grep -E "\.o$$")

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS) 
	@ar rcs $(@) $(OBJS) $(LIB_OBJS)

$(OBJ_DIR):
	mkdir -p $(@)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

# NAME		= ft_printf
# CC			= gcc
# CFLAGS		= -Wall -Wextra -Werror
# EXTRA_FLAGS = -Wpedantic -Wunused -Wconversion -Wunreachable-code -Wtype-limits -O3
# SOURCES		= ft_ftoa.c
# SRCS_DIR	= sources/
# SRCS		= $(addprefix	$(SRCS_DIR), $(SOURCES))
# OBJS		= $(addprefix	$(OBJS_DIR), $(SOURCES:.c=.o))
# OBJS_DIR	= objects/
# INCLUDES	= -I includes -I libft/includes

# all: $(NAME)

# $(NAME): $(OBJS)
# 	@echo "Compiling ..."
# 	@$(CC) $(OBJS) $(INCLUDES) -o $(NAME) -L libft -lft
# 	@echo "Compiled"

# $(OBJS_DIR)%.o:	$(SRCS_DIR)%.c includes/ft_printf.h
# 	@make -sC libft
# 	@mkdir -p $(OBJS_DIR)
# 	@$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	@rm -rf $(OBJS_DIR)
# 	@rm -f libft/objects/*.o
# 	@make clean -C libft/

# fclean: clean 
# 	@rm -f $(NAME)
# 	@rm -f libft/libft.a
# 	@make fclean -C libft/

# re: fclean all

# .PHONY: all clean fclean re