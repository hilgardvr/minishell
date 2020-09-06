# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
#    Updated: 2017/07/22 09:34:03 by gvan-roo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

PATH_HEAD	=	./headers/
PATH_LIB	=	./libft/
PATH_SRSC	=	./srsc/
PATH_OSRC	=	./orsc/

HEADERS		=	minishell.h

SRSC		=	$(PATH_SRSC)main.c		\
				$(PATH_SRSC)setenv.c	\
				$(PATH_SRSC)builtins.c	\
				$(PATH_SRSC)paths.c		\

OSRC		=	main.o		\
				setenv.o	\
				builtins.o	\
				paths.o		\

FLAGS		=	-Wall -Werror -Wextra

all	:	$(NAME)

$(NAME)	:	$(OSRC)
	make -C $(PATH_LIB) fclean && make -C $(PATH_LIB)
	gcc $(FLAGS) -I $(PATH_HEAD)$(HEADERS) -c $(SRSC)
	gcc -o $(NAME) $(OSRC) -L$(PATH_LIB) -lft

$(OSRC) :
	
clean	:
	rm -f $(OSRC)
	make -C $(PATH_LIB) clean

fclean	:	clean
	rm -f $(NAME)
	make -C $(PATH_LIB) fclean

re	:	fclean
	make
