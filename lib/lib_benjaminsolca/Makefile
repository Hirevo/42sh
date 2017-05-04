##
## Makefile for lib in /home/benjamin/Dropbox/lib/
##
## Made by Benjamin
## Login   <benjamin.solca@epitech.eu>
##
## Started on  Wed Apr  5 11:14:13 2017 Benjamin
## Last update Thu May  4 11:03:34 2017 Arthur Knoepflin
##

RM	=	rm -rf

all:
		/bin/echo -e "\n\x1b[1m\x1b[40m==> COMPILE LIB <==\x1b[0m\n"
		/bin/echo -e "\x1b[1m\x1b[37m** Compiling lib: MY **\x1b[0m"
		make -sC my
		/bin/echo -e "\x1b[32m  -Complete-\x1b[0m"
		/bin/echo -e "\x1b[1m\x1b[37m** Compiling lib: MY_PRINTF **\x1b[0m"
		make -sC my_printf
		/bin/echo -e "\x1b[32m  -Complete-\x1b[0m"

d:		CFLAGS += -g -Wall -pedantic
d:		re

clean:
		@rm -f ../*.o


fclean:		clean

re: 		fclean all

.SILENT:	all debug clean fclean
.PHONY:		all debug clean fclean re
