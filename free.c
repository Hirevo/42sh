/*
** free.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 11:12:24 2017 Nicolas Polomack
** Last update Wed Mar 22 23:59:20 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

void		free_alias(t_shell *shell)
{
  t_alias	*last;

  last = NULL;
  while (shell->alias != NULL)
    {
      free(shell->alias->command);
      free(shell->alias->alias);
      if (last != NULL)
	free(last);
      last = shell->alias;
      shell->alias = shell->alias->next;
    }
  if (last != NULL)
    free(last);
}

void	free_shell(t_shell *shell)
{
  int	i;

  i = -1;
  if (shell->path != NULL)
    {
      while (shell->path[++i] != NULL)
        free(shell->path[i]);
      free(shell->path);
    }
  i = -1;
  if (shell->env != NULL)
    {
      while (shell->env[++i] != NULL)
        free(shell->env[i]);
      free(shell->env);
    }
  save_alias(shell);
  (shell->home != NULL) ? free(shell->home) : 0;
  free(shell->current);
  free_shell2(shell);
}

void	free_shell2(t_shell *shell)
{
  int	i;

  i = -1;
  if (shell->final != NULL)
    {
      while (shell->final[++i] != NULL)
	free(shell->final[i]);
      free(shell->final);
    }
  i = -1;
  if (shell->hist != NULL)
    {
      while (shell->hist[++i] != NULL)
        free(shell->hist[i]);
      free(shell->hist);
    }
  free_alias(shell);
  free(shell->last);
  free(shell->prev);
  free(shell->line);
  free(shell->exit_str);
  free_commands(shell);
  if (isatty(0))
    my_printf("exit\n");
}

void		free_commands(t_shell *shell)
{
  int		i;
  t_command	*head;
  t_command	*last;

  head = shell->commands;
  while (head)
    {
      i = -1;
      while (head->av[++i])
	free(head->av[i]);
      free(head->av);
      free(head->r_type);
      free(head->r_name);
      free(head->l_type);
      free(head->l_name);
      last = head;
      head = head->next;
      free(last);
    }
}
