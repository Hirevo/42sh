##
## Makefile for Makefile in /home/nicolas/bin/Makefile
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Tue Apr 18 19:18:58 2017 Nicolas Polomack
##

MAKE1	=	make -sC lib/my --no-print-directory

SRC	=	main.c			\
		init.c			\
		prompt/char.c		\
		prompt/misc.c		\
		prompt/prompt.c		\
		prompt/actions.c	\
		get_next_line.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Llib/my -lmy

REDDARK	=	\033[31;2m

RED	=	\033[31;1m

GREEN	=	\033[32;1m

YEL	=	\033[33;1m

BLUE	=	\033[34;1m

PINK	=	\033[35;1m

CYAN	=	\033[36;1m

RES	=	\033[0m

NAME	=	42sh

PROJ	=	42sh

UPPER	=	$(shell echo $(PROJ) | tr a-z A-Z)

all:	$(NAME)

$(NAME):$(OBJ)
	@echo
	@echo -e "$(GREEN)Everything compiled smoothly. Now compiling dependancies...$(RES)"
	@echo
	@echo -en "$(CYAN)Compiling libmy...$(RES)"
	@$(MAKE1)
	@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo -en "$(CYAN)Linking $(PROJ)...$(RES)"
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) -lncurses
	@echo -e "\t\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
	@echo
	@echo -e "$(GREEN)---- $(UPPER) READY ----$(RES)"
	@echo

clean:
	@$(MAKE1) clean
	@$(foreach var, $(OBJ), if [ -e $(var) ] ; then \
	printf "[$(RED)RM$(RES)] $(YEL)$(var)$(RES)\n" \
	&& $(RM) $(var) ; fi ;)

fclean:	clean
	@$(MAKE1) fclean
	@if [ -e $(NAME) ] ; then \
	printf "[$(RED)RM EXEC$(RES)] $(YEL)$(NAME)$(RES)\n" \
	&& rm -f $(NAME) ; fi

re:	fclean all

%.o:	%.c
	@echo -e "[$(RED)COMPILE$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
	@gcc $(CFLAGS) -o $@ -c $<
