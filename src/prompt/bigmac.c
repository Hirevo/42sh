/*
** bigmac.c for bigmac in /home/arthur/delivery/PSU/PSU_2016_42sh
**
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
**
** Started on  Fri May  5 10:10:32 2017 Arthur Knoepflin
** Last update Sun May  7 23:41:32 2017 Nicolas Polomack
*/

#include "my.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bigmac_prompt(t_shell *shell)
{
	char *login;
	char *hostname;

	fflush(stdout);
	printf("%s", "[");
	if ((login = getenv("LOGNAME")))
		printf("\033[35;1m%s\033[0m", login);
	printf("%s", "@");
	if ((hostname = get_hostname()))
		printf("\033[31;1m%s\033[0m", hostname);
	free(hostname);
	printf("%s", " ");
	if (shell->current)
		printf("\033[32;1m%s\033[0m", shell->current);
	else
		printf("\033[32;1m?\033[0m");
	printf("%s", getuid() ? "]$ " : "]# ");
	fflush(stdout);
}
