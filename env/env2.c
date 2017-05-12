/*
** env2.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:01:50 2017 Nicolas Polomack
** Last update Fri May 12 22:58:57 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	disp_env()
{
  int	i;

  i = -1;
  while (environ[++i] != NULL)
    my_printf("%s\n", environ[i]);
  return (0);
}

int	check_env_error(char *name)
{
  if (name[0] == 0 || ((name[0] < 'a' || name[0] > 'z') &&
                       (name[0] < 'A' || name[0] > 'Z')))
    return (my_print_err("setenv: Variable name must \
begin with a letter.\n"));
  if (!is_char_alpha(name))
    return (my_print_err("setenv: Variable name must") - 1 +
	    my_print_err(" contain alphanumeric characters.\n"));
  return (0);
}
