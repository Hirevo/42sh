/*
** test.c for minishell1 in /home/nicolaspolomack/shell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sat Jan 14 18:04:39 2017 Nicolas Polomack
** Last update Sat May  6 22:46:57 2017 Nicolas Polomack
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "get_next_line.h"
#include "shell.h"
#include "my.h"

int		exec_branch(t_shell *shell, t_command **head,
			    int fds[3], int **pipes)
{
  int		r;

  if (((*head)->link == ';' || (*head)->next == NULL) &&
      exec_redirected_builtins(shell, fds[2], &r, fds) != 0 &&
      close_pipes(*pipes) == 0)
    {
      *pipes = NULL;
      (*head) = (*head)->next;
      return (r);
    }
  r = -1;
  while ((*pipes)[++r]);
  r = ((r - 3) < 0) ? 0 : r - 3;
  if ((*head)->l_type)
    (*pipes)[r] = setup_left_redirect((*head)->l_name,
				      (*head)->l_type[1] == 0);
  if ((fds[2] = fork()) == -1)
    return (84);
  fds[2] ? (r = father_action(head, pipes, fds, shell)) :
    exec_piped_child(*pipes, *head, fds, shell);
  return (r);
}

int		exec_pipeline(t_shell *shell)
{
  int		fds[3];
  int		*pipes;
  t_command	*head;
  int		i;
  int		r;

  pipes = NULL;
  shell->fds = NULL;
  head = shell->commands;
  while (head)
    {
      shell->cur = head;
      fds[2] = -1;
      while (head->av[++(fds[2])]);
      if (pipe(fds) == -1)
	return (ret_error(shell, "Can't make pipe.\n"));
      insert_int(&pipes, fds[1]);
      insert_int(&pipes, fds[0]);
      if ((r = exec_branch(shell, &head, fds, &pipes)) == 84)
	return (84);
    }
  return (r);
}

void	exec_piped_child(int *pipes, t_command *head, int *fds, t_shell *shell)
{
  int	i;
  int	args;

  signal(SIGINT, SIG_DFL);
  setup_exec(head, pipes, fds);
  args = -1 + 0 * (i = 0);
  close(fds[1]);
  while (head->av[++args]);
  if (is_path(shell->cur->av[0]) || exec_builtins(shell, args, &i) == 0)
    if ((i = check_access(shell->cur->av, shell)) >= 0)
      exec_child(shell, i);
    else
      {
        my_print_err(shell->cur->av[0]);
        my_print_err((i == -1) ? ": Command not found.\n" :
		     ": Permission denied.\n");
        i = 1;
      }
  exit(1);
}

int	get_return(t_shell *shell)
{
  int	i;
  int	r;
  int	final;

  i = -1;
  final = 0;
  while (shell->fds[++i])
    {
      waitpid(shell->fds[i], &r, 0);
      if (!WIFEXITED(r))
	diagnose_status(r);
      if (r && !final)
	final = r;
    }
  free(shell->fds);
  shell->fds = NULL;
  return (final);
}

int	father_action(t_command **head, int **pipes, int *fds, t_shell *shell)
{
  int	i;
  int	r;
  int	passed = 0;

  insert_int(&shell->fds, fds[2]);
  r = 0;
  if (!((*head)->next) || (*head)->link != '|')
    {
      r = get_return(shell);
      fds[2] = -1;
      while ((*pipes)[++(fds[2])])
 	close((*pipes)[fds[2]]);
      free(*pipes);
      *pipes = NULL;
    }
  while  ((*head) && (((*head)->link == 'e' && WEXITSTATUS(r)) ||
		      ((*head)->link == 'o' && !WEXITSTATUS(r))))
    (*head) = (*head)->next;
  (*head) = (*head)->next;
  close(fds[1]);
  return (WIFEXITED(r) ? WEXITSTATUS(r) : r % 128 + 128);
}
