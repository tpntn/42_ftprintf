# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 10:24:54 by tpontine          #+#    #+#              #
#    Updated: 2022/10/12 09:42:20 by tpontine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_printf
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
EXTRA_FLAGS = -Wpedantic -Wunused -Wconversion -Wunreachable-code -Wtype-limits -O3
SOURCES		= ft_ftoa.c
SRCS_DIR	= sources/
SRCS		= $(addprefix	$(SRCS_DIR), $(SOURCES))
OBJS		= $(addprefix	$(OBJS_DIR), $(SOURCES:.c=.o))
OBJS_DIR	= objects/
INCLUDES	= -I includes -I libft/includes

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling ..."
	@$(CC) $(OBJS) $(INCLUDES) -o $(NAME) -L libft -lft
	@echo "Compiled"

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c includes/ft_printf.h
	@make -sC libft
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@rm -f libft/objects/*.o
	@make clean -C libft/

fclean: clean 
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re