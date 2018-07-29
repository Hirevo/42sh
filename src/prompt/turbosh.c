/*
** turbosh.c for turbosh in /home/arthur/delivery/PSU/PSU_2016_42sh
**
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
**
** Started on  Thu May  4 23:52:05 2017 Arthur Knoepflin
** Last update Fri May 19 19:08:12 2017 Nicolas Polomack
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void turbosh_prompt(t_shell *shell)
{
	char *str;

	fflush(stdout);
	printf("%s", shell->exit ? "\033[31;1m" : "\033[0m");
	printf("%s", "##\033[0m");
	str = getenv("LOGNAME");
	printf("\033[32;1m%s\033[0m", str ? str : "");
	printf("%s", ":");
	if (shell->current)
		printf("\033[34;1m%s\033[0m", shell->current);
	else
		printf("\033[34;1m?\033[0m");
	printf("%s", getuid() ? "$ " : "# ");
	fflush(stdout);
}
