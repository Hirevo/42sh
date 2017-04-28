/*
** exec2.c for minishell1 in /home/nicolaspolomack/shell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Jan 19 12:54:48 2017 Nicolas Polomack
** Last update Sun Apr  2 20:45:15 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "my.h"
#include "get_next_line.h"
#include "shell.h"

int	compare_stats(struct stat *stats)
{
  if (stats->st_mode & S_IXUSR)
    if (!S_ISDIR(stats->st_mode))
      return (0);
    else
      return (-3);
  else
    return (-2);
}

unsigned int	process_command(t_shell *shell, int i)
{
  unsigned int	args;

  if (i)
    while (shell->line = get_next_line(0))
      {
        if (is_line_empty(shell))
          return (0);
        args = exec_line(shell, 0);
      }
  else
    {
      if ((shell->line = get_next_line(0)) == NULL)
        shell->line = my_strdup("exit");
      if (is_line_empty(shell))
        return (0);
      args = exec_line(shell, 0);
    }
  return (args);
}

unsigned int	exec_redirected_builtins(t_shell *shell, int count,
					 int *i, int fds[2])
{
  int		fd;
  int		last;
  t_command	*head;
  unsigned int	ret;

  head = shell->cur;
  if (!is_builtin(head->av[0]))
    return (0);
  fd = 0;
  close(fds[0]);
  dup2(1, fds[0]);
  if (head->r_type)
    fd = setup_right_redirect(head, fds, (head->r_type[1] == 0));
  ret = exec_builtins(shell, count, i);
  if (fd)
    {
      close(fd);
      dup2(fds[0], 1);
    }
  return (ret);
}
