/*
** history.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:57:32 2017 Nicolas Polomack
** Last update Fri May  5 02:28:47 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int	check_wave(t_shell *shell)
{
  char	*home;
  char	*new;
  int	i;

  if ((home = getenv("HOME")) == NULL ||
      (new = malloc(my_strlen(home) + my_strlen(shell->line) + 1)) == NULL)
    return (0);
  i = 0;
  while (shell->line[i] != 0 && shell->line[i] != '~')
    new[i] = shell->line[i++];
  new[i] = 0;
  if (shell->line[i] == 0)
    {
      free(new);
      return (0);
    }
  new = my_strcat(new, home);
  new = my_strcat(new, shell->line + i + 1);
  free(shell->line);
  shell->line = my_strdup(new);
  free(new);
  return (1);
}

void	add_hist(t_shell *shell)
{
  int	i;
  int	l;
  int	j;

  j = 0;
  l = -1;
  while (shell->hist[++l]);
  l -= 1;
  i = -1;
  while (shell->final[++i])
    {
      if (my_strcmp(shell->final[i], "!$") == 0)
        {
          free(shell->final[i]);
          shell->final[i] = my_strdup(shell->hist[l]);
          j = 1;
        }
      if (my_strcmp(shell->final[i], "$?") == 0)
        {
          free(shell->final[i]);
          shell->final[i] = my_int_to_char(shell->exit);
        }
    }
  if (j)
    my_print_command(shell);
}
