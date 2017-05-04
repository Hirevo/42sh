##
## Makefile for Makefile in /home/prodjia/delivery/PSU_2016_my_printf
##
## Made by Benjamin
## Login   <prodjia@epitech.net>
##
## Started on  Mon Nov  7 15:46:52 2016 Benjamin
## Last update Mon Apr 17 16:14:20 2017 Benjamin
##

RM	=	rm -rf

SRC	=	prtf.c	\
		my_fonc.c	\
		my_fonc2.c	\
		my_fonc3.c	\
		my_check.c	\
		my_the_fonc.c	\
		my_the_fonc2.c	\
		my_the_fonc3.c	\

NAME	= 	../../libmy_printf.a

OBJ	= 	$(SRC:.c=.o)

CFLAGS	+=		-I../../../include/

all:		$(NAME)

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)

d:		CFLAGS += -g -Wall -pedantic
d:		re

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
