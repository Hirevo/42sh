/*
** set.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 18 20:41:29 2017 Nicolas Polomack
** Last update Thu May 18 23:08:25 2017 Nicolas Polomack
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int	disp_vars(t_shell *shell)
{
  int	i;

  i = -1;
  if (shell->vars)
    while (shell->vars[++i])
      printf("%s\n", shell->vars[i]);
  return (0);
}

int	set(t_shell *shell, int args)
{
  char	*str;
  char	*comp;
  int	i;
  int	j;

  if (args == 1)
    return (disp_vars(shell));
  else
    {
      i = 0;
      while (shell->cur->av[++i])
	{
	  if ((str = strdup(shell->cur->av[i])) == NULL
	      || (comp = strsep(&str, "=")) == NULL)
	    return (1);
	  add_var(shell, comp, str);
	  free(comp);
	}
    }
}
