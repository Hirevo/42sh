/*
** my_exec.c for my_exec in /home/nicolaspolomack/shell/bs_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Jan  3 09:03:30 2017 Nicolas Polomack
** Last update Fri May  5 00:54:04 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "my.h"
#include "get_next_line.h"
#include "shell.h"

void	diagnose_status(unsigned int status)
{
  if ((status % 128) == SIGSEGV)
    my_print_err("Segmentation fault");
  else if ((status % 128) == SIGFPE)
    my_print_err("Floating exception");
  else if ((status % 128) == SIGBUS)
    my_print_err("Bus error");
  else if ((status % 128) == SIGABRT)
    my_print_err("Aborted");
  else if ((status % 128) == SIGILL)
    my_print_err("Illegal instruction");
  else if ((status % 128) == SIGKILL)
    my_print_err("Killed");
  else if ((status % 128) == SIGTERM)
    my_print_err("Terminated");
  else if ((status % 128) == SIGPIPE)
    return ;
  my_print_err((WCOREDUMP(status)) ? " (core dumped)\n" : "\n");
}

void		reload_shell(t_shell *shell)
{
  int		i;
  int		k;

  i = -1;
  while (shell->env && shell->env[++i])
    if (!my_strncmp(shell->env[i], "PATH=", 4))
      {
	if (shell->path)
          {
	    k = -1;
            while (shell->path[++k])
	      free(shell->path[k]);
            free(shell->path);
          }
	shell->path = init_path(shell->env);
	break;
      }
  if (shell->home != NULL)
    free(shell->home);
  shell->home = get_home(shell->env);
  shell->current = get_current(shell->current, shell->home);
}

int	init_shell(t_shell *shell, char **ae)
{
  shell->exit = 0;
  shell->prompt = 0;
  shell->env = copy_env(ae);
  shell->path = init_path(shell->env);
  shell->home = get_home(shell->env);
  if ((shell->current = malloc(512)) == NULL)
    return (-1);
  shell->current[0] = 0;
  shell->current = get_current(shell->current, shell->home);
  shell->exit = 0;
  shell->last = NULL;
  shell->prev = NULL;
  shell->hist = NULL;
  shell->exit_str = NULL;
  shell->fds = NULL;
  shell->is_done = 0;
  init_aliases(shell);
  parse_path(shell);
  shell->path = (shell->path) ? shell->path : set_default_path();
  return (0);
}

int		main(int ac, char **av, char **ae)
{
  int		exit;
  t_shell	shell;

  exit = 0;
  signal(SIGINT, SIG_IGN);
  if (init_shell(&shell, ae) == -1)
    return (84);
  if (!isatty(0))
    exit = process_command(&shell, 1);
  else
    while (1)
      {
	print_prompt(&shell);
	shell.exit = process_command(&shell, 0);
      }
  return (exit);
}
