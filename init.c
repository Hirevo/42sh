/*
** init.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 18:57:40 2017 Nicolas Polomack
** Last update Tue May 16 20:56:51 2017 Nicolas Polomack
*/

#include <curses.h>
#include <term.h>
#include <string.h>
#include <unistd.h>
#include <termio.h>
#include <sys/ioctl.h>
#include "shell.h"

void		set_raw(struct termio *oterm)
{
  struct termio	nterm;

  nterm = *oterm;
  nterm.c_lflag &= ~(ICANON | ECHO);
  nterm.c_cc[VTIME] = 0;
  nterm.c_cc[VMIN] = 0;
  if (ioctl(0, TCSETA, &nterm) == -1)
    handle_error("ioctl");
}

void	init(t_shell *shell)
{
  shell->tty = isatty(0);
  if (shell->tty)
    {
      setupterm(NULL, 0, NULL);
      printf(tigetstr("smkx"));
      fflush(stdout);
      shell->ioctl = ioctl(0, TCGETA, &shell->w.oterm) + 1;
      shell->w.clear = tigetstr("clear");
      shell->w.end = tigetstr("kend");
      shell->w.home = tigetstr("khome");
      shell->w.forw = tigetstr("cuf1");
      shell->w.backw = tigetstr("cub1");
      shell->w.upw = tigetstr("kcuu1");
      shell->w.downw = tigetstr("kcud1");
      shell->w.left = tigetstr("kcub1");
      shell->w.right = tigetstr("kcuf1");
      shell->line = NULL;
    }
}

void	init_prompt(t_shell *shell)
{
  if (shell->tty)
    {
      get_prompt(shell);
      sauv_prompt(shell);
      print_prompt(shell);
    }
}
