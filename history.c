/*
** history.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu May 11 20:41:13 2017 Nicolas Polomack
** Last update Fri May 12 21:46:18 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "server.h"
#include "shell.h"
#include "my.h"

void		write_hist(t_shell *shell, int fd)
{
  t_history	*head;
  t_history	*last;
  int		i;

  head = shell->hist.first;
  while (head)
    {
      last = head;
      i = -1;
      while (head->cmd[++i])
        {
          dprintf(fd, i ? " %s" : "%s", head->cmd[i]);
          free(head->cmd[i]);
        }
      dprintf(fd, "\n");
      free(head->cmd);
      head = head->next;
      free(last);
    }
  close(fd);
}

void		save_history(t_shell *shell)
{
  int		fd;
  char		*line;

  if (shell->hist.first == NULL || shell->home == NULL ||
      (line = malloc(512)) == NULL)
    return ;
  line[0] = 0;
  line = strcat(line, shell->home);
  if (shell->home[strlen(shell->home)] != '/')
    line[strlen(shell->home)] = '/';
  line[strlen(shell->home) + 1] = 0;
  line = my_strcat(line, HIST_FILE);
  if ((fd = open(line, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    return ;
  free(line);
  write_hist(shell, fd);
}

int		disp_hist(t_shell *shell)
{
  t_history	*head;
  int		i;
  int		index;

  if (shell->hist.first == NULL)
    return (0);
  index = 0;
  head = shell->hist.first;
  while (head)
    {
      index += 1;
      printf("%6d   ", index);
      i = -1;
      while (head->cmd[++i])
	printf(i ? " %s" : "%s", head->cmd[i]);
      printf("\n");
      head = head->next;
    }
  return (0);
}

void	add_hist_elem(t_shell *shell, char *line)
{
  t_history	*elem;

  elem = malloc(sizeof(t_history));
  elem->cmd = my_split_mulchar(line, " \t");
  elem->next = NULL;
  elem->prev = NULL;
  if (shell->hist.last)
    {
      shell->hist.last->next = elem;
      elem->prev = shell->hist.last;
      shell->hist.last = elem;
    }
  else
    {
      shell->hist.first = elem;
      shell->hist.last = elem;
    }
}

void	init_history(t_shell *shell)
{
  int	fd;
  char	*line;

  shell->hist.cur = NULL;
  shell->hist.last = NULL;
  shell->hist.first = NULL;
  if ((shell->home == NULL) || (line = malloc(512)) == NULL)
    return ;
  line[0] = 0;
  line = strcat(line, shell->home);
  if (shell->home[strlen(shell->home)] != '/')
    line[strlen(shell->home)] = '/';
  line[strlen(shell->home) + 1] = 0;
  line = my_strcat(line, HIST_FILE);
  if ((fd = open(line, O_RDONLY)) == -1)
    return ;
  free(line);
  while (line = get_next_line(fd))
    {
      add_hist_elem(shell, line);
      free(line);
    }
  close(fd);
}
