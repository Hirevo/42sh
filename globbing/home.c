/*
** home.c for 42sh in /home/nicolaspolomack/TurboSh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat May 13 21:14:22 2017 Nicolas Polomack
** Last update Sat May 20 21:47:32 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

static int	skip_spaces(t_shell *shell, int *i)
{
  while (is_space(shell->line[*i]))
    *i += 1;
  *i -= 1;
  return (1);
}

static void	other_case(t_shell *shell, int *i, int *can_edit)
{
  while (shell->line[*i] && !is_separator(shell->line[*i]) &&
         !is_space(shell->line[*i]))
    *i += 1;
  *i -= 1;
  *can_edit = 1;
}

static void	insert_home(t_shell *shell, int i)
{
  int		ret;
  char		*str;

  ret = asprintf(&str, "%.*s%s%s", i, shell->line, shell->home,
               shell->line + i + 1);
  if (ret == -1 || str == NULL)
    handle_error("malloc");
  free(shell->line);
  shell->line = str;
}

void	replace_home(t_shell *shell)
{
  int	i;
  int	can_edit;

  if (shell->home == NULL)
    return ;
  i = -1;
  can_edit = 1;
  while (shell->line[++i])
    if (is_space(shell->line[i]))
      can_edit = skip_spaces(shell, &i);
    else if (is_delimiter(shell->line[i]))
      can_edit = 1;
    else if (shell->line[i] == '\'' || shell->line[i] == '"')
      {
	i += 1;
        while (shell->line[i] && shell->line[i] != '\''
	       && shell->line[i] != '"')
          i += 1;
	i -= (shell->line[i] == 0) ? 1 : 0;
      }
    else if (shell->line[i] == '~' && can_edit)
      insert_home(shell, i);
    else
      can_edit = 0;
}
