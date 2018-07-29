/*
** mysh.c for 42sh in /home/nicolaspolomack/psu/PSU_2016_42sh/prompt
**
** Made by nicolaspolomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Jul 24 01:07:30 2017 nicolaspolomack
** Last update Sat Nov 17 07:35:31 2017 Nicolas Polomack
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void mysh(t_shell *shell)
{
	char *git = 0;

	fflush(stdout);
	if (shell->exit_str)
		printf("\e[1m\e[38;2;255;85;85m(%s)\e[0m ", shell->exit_str);
	printf(
		"\e[1m\e[38;2;255;85;85m42sh\e[21m\e[0m \e[38;2;38;252;166m");
	if (shell->current != NULL)
		printf("%s", shell->current);
	printf("\e[0m ");
	git = show_cur_branch();
	if (git)
		printf("[\e[1m\e[38;2;0;133;255m%s\e[0m] ", git);
	printf(getuid() ? "$" : "#");
	printf(">\e[1m ");
	fflush(stdout);
}
