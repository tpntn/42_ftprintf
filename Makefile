# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpontine <tpontine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 10:24:54 by tpontine          #+#    #+#              #
#    Updated: 2022/09/22 15:01:06 by tpontine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf
SRCS = main ft_ftoa
FILES = $(patsubst %, %.c, $(SRCS))
OBJECTS = $(patsubst %, %.o, $(SRCS))
FLAGS = -g

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(FLAGS) -c $(FILES)
	gcc $(FLAGS) $(OBJECTS) libft/libft.a -o $(NAME)
	make fclean -C libft/

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all