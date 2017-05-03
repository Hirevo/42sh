##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Wed May  3 11:33:19 2017 Benjamin
##

MAKE1	=	make -sC lib/my --no-print-directory

MAKE2	=	make -sC lib/lib_benjaminsolca --no-print-directory

SRC	=	alias/alias.c		\
		alias/alias2.c		\
		alias/alias3.c		\
		parse/bufferize.c	\
		builtins.c		\
		cd.c			\
		env/env.c		\
		env/env2.c		\
		exec/exec.c		\
		exec/exec2.c		\
		exec/pipe.c		\
		exec/close.c		\
		exec/setup.c		\
		free.c			\
		history.c		\
		history2.c		\
		home.c			\
		misc.c			\
		parse/parse.c		\
		parse/error.c		\
		path/path.c		\
		path/path2.c		\
		print.c			\
		my_sh.c			\
		exit.c			\
		parse/line.c		\
		redirects.c		\
		buffer.c		\
		char.c			\
		is/is.c			\
		is/is2.c		\
		get_next_line.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -Llib -lmy -lbs -lmy_printf

REDDARK	=	\033[31;2m

RED	=	\033[31;1m

GREEN	=	\033[32;1m

YEL	=	\033[33;1m

BLUE	=	\033[34;1m

PINK	=	\033[35;1m

CYAN	=	\033[36;1m

RES	=	\033[0m

NAME	=	42sh

all:	$(NAME)

$(NAME):$(OBJ)
	@echo
	@echo -e "$(GREEN)Everything compiled smoothly. Now compiling dependancies...$(RES)"
	@echo
	@echo -en "$(CYAN)Compiling libmy...$(RES)"
	@$(MAKE1)
	@$(MAKE2)
	@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo -en "$(CYAN)Linking TurboSh...$(RES)"
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)
	@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo
	@echo -e "$(GREEN)---- TURBOSH READY ----$(RES)"
	@echo

clean:
	@$(MAKE1) clean
	@$(MAKE2) clean
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then \
	printf "[$(RED)RM$(RES)] $(YEL)$(var)$(RES)\n" \
	&& $(RM) $(var) ; fi ;)

fclean:	clean
	@$(MAKE1) fclean
	@$(MAKE2) fclean
	@if [ -e $(NAME) ] ; then \
	printf "[$(RED)RM EXEC$(RES)] $(YEL)$(NAME)$(RES)\n" \
	&& rm -f $(NAME) ; fi

re:	fclean all

%.o:	%.c
	@echo -e "[$(RED)COMPILE$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
	@gcc $(CFLAGS) -o $@ -c $<
