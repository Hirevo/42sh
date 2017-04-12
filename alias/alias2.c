/*
** alias2.c for minishell1 in /home/nicolaspolomack/shell/PSU_2016_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Jan  9 10:42:33 2017 Nicolas Polomack
** Last update Sat Mar 25 21:52:16 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"

int		add_alias(t_shell *shell, char *alias,
			  char *command)
{
  t_alias	*elem;

  elem = shell->alias;
  while (elem != NULL)
    {
      if (my_strcmp(elem->alias, alias) == 0)
        {
          free(elem->command);
          elem->command = my_strdup(command);
          return (0);
        }
      elem = elem->next;
    }
  if ((elem = malloc(sizeof(t_alias))) == NULL)
    return (1);
  elem->alias = my_strdup(alias);
  elem->command = my_strdup(command);
  elem->next = shell->alias;
  shell->alias = elem;
  return (0);
}

int		disp_all_alias(t_shell *shell)
{
  t_alias	*head;

  if (shell->alias == NULL)
    return (0);
  head = shell->alias;
  while (head != NULL)
    {
      my_printf("alias %s='%s'\n", head->alias, head->command);
      head = head->next;
    }
  return (0);
}

int		disp_alias(t_shell *shell, char *alias)
{
  t_alias	*head;

  if (shell->alias == NULL)
    return (0);
  head = shell->alias;
  while (head != NULL)
    {
      if (my_strcmp(head->alias, alias) == 0)
        my_printf("alias %s='%s'\n", head->alias, head->command);
      head = head->next;
    }
  return (0);
}
