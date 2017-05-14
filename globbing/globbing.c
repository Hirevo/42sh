/*
** globbing.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:57:32 2017 Nicolas Polomack
** Last update Sat May 13 21:31:13 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

static char	*get_var(char *str)
{
  int	i;

  i = 0;
  while (str[i] && is_alphanum(str[i]))
    i += 1;
  return (strndup(str, i));
}

static int	replace_var(t_shell *shell, int *cur, char *var)
{
  char	*str;
  int	i;

  i = 0;
  if (!strncmp(shell->line + *cur, "$?", 2))
    i = asprintf(&str, "%.*s%d%s", *cur, shell->line, shell->exit,
		 shell->line + *cur + 2);
  else if (!strncmp(shell->line + *cur, "$$", 2))
    i = asprintf(&str, "%.*s%d%s", *cur, shell->line, getpid(),
		 shell->line + *cur + 2);
  else if (!getenv(var))
    {
      dprintf(2, "%s: Undefined variable.\n", var);
      return (-1);
    }
  else
    i = asprintf(&str, "%.*s%s%s", *cur, shell->line, getenv(var),
		 shell->line + *cur + strlen(var) + 1);
  if (i == -1 || str == NULL)
    handle_error("malloc");
  *cur += (strlen(str) - strlen(shell->line)) + 1;
  free(shell->line);
  shell->line = str;
  return (0);
}

int	parse_vars(t_shell *shell)
{
  int	cur;
  char	*var;

  cur = -1;
  while (shell->line[++cur])
    {
      if (shell->line[cur] == '\'')
	while (shell->line[cur + 1] && shell->line[cur + 1] != '\'')
	  cur += 1;
      else if (shell->line[cur] == '$')
	{
	  if ((var = get_var(shell->line + cur + 1)) == NULL)
	    exit(84);
	  if (replace_var(shell, &cur, var) == -1)
	    return (-1);
	}
    }
}
