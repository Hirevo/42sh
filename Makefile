##
## Makefile for Makefile in /home/arthur/Documents/Sock
## 
## Made by Arthur Knoepflin
## Login   <arthur.knoepflin@epitech.eu>
## 
## Started on  Sat Apr 22 14:22:00 2017 Arthur Knoepflin
## Last update Sat Apr 29 22:30:46 2017 Arthur Knoepflin
##

SRC	=	add_env_http.c		\
		char_double.c		\
		client.c		\
		com_serv.c		\
		exec_cmd_http.c		\
		decode.c		\
		get_env.c		\
		get_file_http.c		\
		get_next_line.c		\
		init_connection.c	\
		indexof.c		\
		int_toc.c		\
		main.c			\
		my_split.c		\
		my_split_char.c		\
		my_split_mulchar.c	\
		navigator.c		\
		prompt.c		\
		response.c		\
		send_env.c		\
		send_file_http.c	\
		send_mime.c

OBJ	=	$(SRC:.c=.o)

NAME	=	config

CFLAGS	+=	-Iinclude -g

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) -lmy -Llib

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all
