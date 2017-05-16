/*
** builtins_tmp.c for builtins in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Mon May 15 10:51:54 2017 Arthur Knoepflin
** Last update Tue May 16 15:34:15 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

static const char	built_tab[][11] = 
{
  "alias", "cd", "config", "dualcast", "echo", "exit",
  "setenv", "unalias", "unsetenv", "builtins", ""
};

static int	show_builtins(t_shell *shell, int args)
{
  char		*ret;
  int		i;
  char		*str;

  i = 0;
  ret = strdup("echo \"");
  while (strlen((char *) built_tab[i]))
    {
      ret = my_fstrcat(ret, (char *) built_tab[i], 1);
      ret = my_fstrcat(ret, "\n", 1);
      i += 1;
    }
  ret = my_fstrcat(ret, "\" | sort | column", 1);
  quick_exec(shell, ret);
  return (0);
}

static int	nb_built(const char str[][11])
{
  int		i;

  i = 0;
  while (my_strlen((char *) built_tab[i]))
    i += 1;
  return (i);
}

static int	indexof_builtin(char *cmd)
{
  int		i;

  i = 0;
  while (my_strlen((char *) built_tab[i]))
    {
      if (!my_strcmp(cmd, (char *) built_tab[i]))
	return (i);
      i += 1;
    }
  return (-1);
}

int	exec_builtins(t_shell *shell, int args, int *r)
{
  int	(*built_fnt[nb_built(built_tab)])(t_shell *, int);
  int	idx;

  built_fnt[0] = &alias;
  built_fnt[1] = &cd_b;
  built_fnt[2] = &config_b;
  built_fnt[3] = &dualcast_b;
  built_fnt[4] = &echo_b;
  built_fnt[5] = &exit_b;
  built_fnt[6] = &setenv_b;
  built_fnt[7] = &unalias_b;
  built_fnt[8] = &setenv_b;
  built_fnt[9] = &show_builtins;
  idx = indexof_builtin(shell->cur->av[0]);
  if (idx >= 0)
    {
      *r = built_fnt[idx](shell, args);
      return (1);
    }
  return (0);
}
