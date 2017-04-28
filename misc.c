/*
** misc.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:07:58 2017 Nicolas Polomack
** Last update Sun Jan 22 01:16:46 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	is_valid_path(char *path)
{
  int	i;

  i = 0;
  if (path[i] == '=')
    return (0);
  while (path[i] != '=')
    if (path[i++] == 0)
      return (0);
  return (1);
}

unsigned int	get_unsigned_int(char *final)
{
  int		i;
  unsigned int	factor;
  unsigned int	result;

  factor = 1;
  i = my_strlen(final) - 1;
  result = 0;
  while (i >= 0)
    {
      if (final[i] == '-')
        result = 256 - result;
      else
        {
          result += (final[i] - '0') * factor;
          factor *= 10;
        }
      i -= 1;
    }
  return (result);
}

int	is_line_empty(t_shell *shell)
{
  int	i;

  i = -1;
  while (shell->line[++i] != 0)
    if (shell->line[i] != ' ' && shell->line[i] != '\t')
      return (0);
  free(shell->line);
  return (1);
}

int	is_char_alpha(char *c)
{
  int	i;

  i = -1;
  while (c[++i])
    {
      if ((c[i] < '0' || c[i] > '9') && (c[i] < 'a' || c[i] > 'z') &&
	  (c[i] < 'A' || c[i] > 'Z') && c[i] != '_')
	return (0);
    }
  return (1);
}

int	my_strlen_spe(char *path, char stop)
{
  int	i;

  i = 0;
  while (path[i] != stop && path[i] != 0)
    i += 1;
  return (i);
}
