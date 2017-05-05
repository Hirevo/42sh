/*
** init.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 18:57:40 2017 Nicolas Polomack
** Last update Fri May  5 05:55:34 2017 Nicolas Polomack
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
      if (ioctl(0, TCGETA, &shell->w.oterm) == -1)
        handle_error("ioctl");
      set_raw(&shell->w.oterm);
      shell->w.clear = tigetstr("clear");
      shell->w.forw = tigetstr("cuf1");
      shell->w.backw = tigetstr("cub1");
      shell->w.left = "\033[D";
      shell->w.right = "\033[C";
      shell->line = NULL;
    }
}

void	init_prompt(t_shell *shell)
{
  if (!shell->tty)
    return ;
  print_prompt(shell);
}
