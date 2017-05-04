##
## Makefile for Makefile in /home/benjamin/Dropbox/func/
##
## Made by Benjamin
## Login   <benjamin.solca@epitech.eu>
##
## Started on  Sun Apr  2 19:26:50 2017 Benjamin
## Last update Tue Apr 25 10:06:56 2017 Benjamin
##

RM	=	rm -rf

SRC	=	my_concat.c			\
  		my_cpy_tab.c			\
		my_epur_str.c			\
		my_find_prime_sup.c		\
		my_getnbr.c			\
		my_memset.c			\
		my_power_rec.c			\
		my_put_error.c			\
		my_put_nbr_base.c		\
		my_put_nbr.c			\
		my_putchar.c			\
		my_putstr.c			\
		my_revstr.c			\
		my_show_tab.c			\
		my_showmem.c			\
		my_showstr.c			\
		my_sort_int_tab.c		\
		my_sort_wordtab.c		\
		my_square_root.c		\
		my_str_to_wordtab.c		\
		my_strcapitalize.c		\
		my_strcat.c			\
		my_strcmp.c			\
		my_strcpy.c			\
		my_strdup.c			\
		my_strlen.c			\
		my_strlowcase.c			\
		my_strncat.c			\
		my_strncmp.c			\
		my_strncpy.c			\
		my_strstr.c			\
		my_strupcase.c			\
		my_swap.c			\
		free_it/free_tab.c		\
		is_it/is_alpha.c		\
		is_it/is_alphanum.c		\
		is_it/is_lower.c		\
		is_it/is_neg.c			\
		is_it/is_num.c			\
		is_it/is_prime.c		\
		is_it/is_printable.c		\
		is_it/is_str_anum.c		\
		is_it/is_str_char.c		\
		is_it/is_str_num.c		\
		is_it/is_upper.c		\
		count_it/cnt_str_char.c		\
		count_it/cnt_line_tab.c		\


NAME	= 	../../libbs.a

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
