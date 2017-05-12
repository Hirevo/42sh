/*
** history2.c for minishell2 in /home/nicolaspolomack/shell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Apr  6 13:59:24 2017 Nicolas Polomack
** Last update Fri May 12 23:04:02 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"

int	insert_one_hist(t_shell *shell, int i, int n)
{
  int	len;
  char	*str;

  if (!shell->hist.last)
    return (-1);
  len = -1;
  while (shell->hist.last->cmd[++len]);
  if (n >= len)
    return (ret_error(shell, "Bad ! arg selector.\n"));
  len = my_strlen(shell->hist.last->cmd[n]);
  len += my_strlen(shell->line) - 3;
  if ((str = malloc(len + 1)) == NULL)
    return (-1);
  my_strncpy(str, shell->line, i);
  my_strcat(str, shell->hist.last->cmd[n]);
  my_strcat(str, shell->line + i + 3);
  free(shell->line);
  shell->line = str;
  return (0);
}

int	insert_full_hist(t_shell *shell, int i)
{
  int	len;
  int	l;
  char	*str;
  char	**cmd;

  if (!shell->hist.last)
    return (-1);
  cmd = shell->hist.last->cmd;
  len = 0;
  l = -1;
  while (cmd[++l])
    len += my_strlen(cmd[l]);
  len += my_strlen(shell->line) - 2 + l;
  if ((str = malloc(len + 1)) == NULL)
    return (-1);
  my_strncpy(str, shell->line, i);
  l = -1;
  while (cmd[++l])
    my_strcat(l ? my_strcat(str, " ") : str,
	      cmd[l]);
  my_strcat(str, shell->line + i + 2);
  free(shell->line);
  shell->line = str;
  return (0);
}

int	insert_last_hist(t_shell *shell, int i)
{
  int	len;
  int	l;
  char	*str;
  char	**cmd;

  if (!shell->hist.last)
    return (-1);
  cmd = shell->hist.last->cmd;
  l = -1;
  while (cmd[++l]);
  l -= 1;
  len = my_strlen(cmd[l]);
  len += my_strlen(shell->line) - 2;
  if ((str = malloc(len + 1)) == NULL)
    return (-1);
  my_strncpy(str, shell->line, i);
  my_strcat(str, cmd[l]);
  my_strcat(str, shell->line + i + 2);
  free(shell->line);
  shell->line = str;
  return (0);
}

int	parse_history(t_shell *shell)
{
  int	i;
  char	*last;

  i = -1;
  last = shell->line;
  while (shell->hist.last && shell->line[++i])
    if (my_strncmp(shell->line + i, "!!", 2) == 0)
      {
	if (insert_full_hist(shell, i) == -1)
	  return (-1);
      }
    else if (my_strncmp(shell->line + i, "!$", 2) == 0)
      {
	if (insert_last_hist(shell, i) == -1)
	  return (-1);
      }
    else if (my_strncmp(shell->line + i, "!:", 2) == 0 &&
	     (shell->line[i + 2] >= '0' &&
	      shell->line[i + 2] <= '9'))
      if (insert_one_hist(shell, i, shell->line[i + 2] - '0') == -1)
	return (-1);
  if (last != shell->line)
    my_printf("%s\n", shell->line);
  return (0);
}
