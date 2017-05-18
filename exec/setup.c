/*
** setup.c for minishell2 in /home/nicolaspolomack/shell2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Apr  2 20:42:53 2017 Nicolas Polomack
** Last update Thu May 18 13:42:22 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void	init_redirect(t_command *head, int *r,
		      int *l, int *i)
{
  *r = 0;
  *l = 0;
  *i = -1;
  head->r_name = NULL;
  head->r_type = NULL;
  head->l_name = NULL;
  head->l_type = NULL;
}

void	setup_exec(t_command *head, int *fds, int ret)
{
  int	i;

  dup2(ret, 0);
  if (ret != 0)
    close(ret);
  if (head->next && head->link == '|')
    dup2(fds[1], 1);
  else if (head->r_type)
    if (setup_right_redirect(head, fds, (head->r_type[1] == 0)) == -1)
      exit(1);
}

void	skip_commands(t_command **head, unsigned char ret)
{
  char	last;

  if ((*head) && (((*head)->link == 'e' && ret)
		  || ((*head)->link == 'o' && !ret)))
    {
      last = (*head)->link;
      (*head) = (*head)->next;
      while ((*head) && (*head)->link != ';' &&
	     (*head)->link != 'e' && (*head)->link != 'o')
	(*head) = (*head)->next;
      if ((*head) && (*head)->link == 'e' && last == 'o')
	ret = 1;
      if ((*head) && (*head)->link != ';')
	skip_commands(head, ret);
    }
}

void	set_fground(t_shell *shell, int pid)
{
  tcsetpgrp(0, pid);
}
