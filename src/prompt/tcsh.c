/*
** tcsh.c for tcsh in /home/arthur/delivery/PSU/PSU_2016_42sh
**
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
**
** Started on  Fri May  5 00:18:47 2017 Arthur Knoepflin
** Last update Fri May 12 13:49:41 2017 Nicolas Polomack
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void tcsh_prompt(t_shell *shell)
{
	char *hostname;

	fflush(stdout);
	if ((hostname = get_hostname()))
		printf("\e[4m%s\e[0m", hostname);
	free(hostname);
	printf("%s", ":");
	if (shell->current)
		printf("\e[1m%s\e[0m", shell->current);
	else
		printf("\e[1m?\e[0m");
	printf("%s", "> ");
	fflush(stdout);
}
