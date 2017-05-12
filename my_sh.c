/*
** my_exec.c for my_exec in /home/nicolaspolomack/shell/bs_minishell1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Tue Jan  3 09:03:30 2017 Nicolas Polomack
** Last update Fri May 12 12:03:16 2017 Nicolas Polomack
*/

#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
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
  char		*path;

  if ((path = getenv("PATH")))
    if (shell->path)
      {
	k = -1;
	while (shell->path[++k])
	  free(shell->path[k]);
	free(shell->path);
      }
  shell->path = init_path(path);
  shell->home = getenv("HOME");
  shell->current = get_current(shell->current, shell->home);
}

int	init_shell(t_shell *shell, char **ae)
{
  srand(getpid() * time(NULL));
  shell->exit = 0;
  shell->path = init_path(getenv("PATH"));
  shell->home = getenv("HOME");
  if ((shell->current = malloc(512)) == NULL)
    return (-1);
  shell->current[0] = 0;
  shell->current = get_current(shell->current, shell->home);
  shell->exit = 0;
  shell->last = NULL;
  shell->prev = NULL;
  shell->exit_str = NULL;
  shell->fds = NULL;
  shell->is_done = 0;
  init_history(shell);
  init_aliases(shell);
  parse_rc(shell);
  shell->path = (shell->path) ? shell->path : set_default_path();
  get_prompt(shell);
  init(shell);
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
  while (1)
    {
      shell.line = NULL;
      shell.w.cur = 0;
      init_prompt(&shell);
      prompt_line(&shell);
      if (shell.line && shell.tty)
        write(1, "\n", 1);
      if (!shell.line)
        shell.line = strdup("exit");
      if (!is_line_empty(&shell))
	shell.exit = exec_line(&shell, 0);
    }
  if (shell.tty)
    if (write(1, "exit\n", 5) == -1 ||
	ioctl(0, TCSETA, &shell.w.oterm) == -1)
      handle_error("ioctl");
  return (shell.exit);
}
