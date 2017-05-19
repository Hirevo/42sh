/*
** builtins_tmp.c for builtins in /home/arthur/delivery/PSU/PSU_2016_42sh
**
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
**
** Started on  Mon May 15 10:51:54 2017 Arthur Knoepflin
** Last update Fri May 19 19:06:41 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "builtin.h"
#include "my.h"

static const char	*g_built_tab[] =
  {
    "alias",
    "cd",
    "config",
    "dualcast",
    "history",
    "echo",
    "exit",
    "setenv",
    "unalias",
    "unsetenv",
    "builtins",
    "prompt",
    "env",
    "set",
    "unset",
    NULL
  };

static int	show_builtins(t_shell *shell, int args)
{
  char		*ret;
  int		i;
  char		*str;

  i = 0;
  ret = strdup("echo '");
  while (g_built_tab[i])
    {
      ret = my_fstrcat(ret, (char *) g_built_tab[i], 1);
      ret = my_fstrcat(ret, "\n", 1);
      i += 1;
    }
  ret = my_fstrcat(ret, "' | sort | column", 1);
  quick_exec(shell, ret);
  return (0);
}

static int	nb_built(const char **str)
{
  int		i;

  i = 0;
  while (g_built_tab[i])
    i += 1;
  return (i);
}

char	**get_builtin_tab()
{
  int	i;
  char	**ret;

  if ((ret = malloc(sizeof(char *) *
		    (nb_built(g_built_tab) + 1))) == NULL)
    return (NULL);
  i = 0;
  while (g_built_tab[i])
    {
      ret[i] = my_strdup((char *) g_built_tab[i]);
      i += 1;
    }
  ret[i] = NULL;
  return (ret);
}

int	indexof_builtin(char *cmd)
{
  int	i;

  i = 0;
  while (g_built_tab[i])
    {
      if (!my_strcmp(cmd, (char *) g_built_tab[i]))
	return (i);
      i += 1;
    }
  return (-1);
}

int	exec_builtins(t_shell *shell, int args, int *r)
{
  int	(*built_fnt[nb_built(g_built_tab)])(t_shell *, int);
  int	idx;

  built_fnt[0] = &alias;
  built_fnt[1] = &cd_b;
  built_fnt[2] = &config_b;
  built_fnt[3] = &dualcast_b;
  built_fnt[4] = &disp_hist;
  built_fnt[5] = &echo_b;
  built_fnt[6] = &exit_b;
  built_fnt[7] = &setenv_b;
  built_fnt[8] = &unalias_b;
  built_fnt[9] = &unsetenv_b;
  built_fnt[10] = &show_builtins;
  built_fnt[11] = &prompt;
  built_fnt[12] = &env_b;
  built_fnt[13] = &set;
  built_fnt[14] = &unset;
  idx = indexof_builtin(shell->cur->av[0]);
  if (idx >= 0 && idx < nb_built(g_built_tab))
    {
      *r = built_fnt[idx](shell, args);
      return (1);
    }
  return (0);
}
