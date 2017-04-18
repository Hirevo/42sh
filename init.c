/*
** init.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 18:57:40 2017 Nicolas Polomack
** Last update Tue Apr 18 19:03:10 2017 Nicolas Polomack
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
    }
}

void	init_prompt(t_shell *shell)
{
  if (!shell->tty)
    return ;
  shell->cwd = getcwd(NULL, 0);
  write(1, RED, strlen(RED));
  write(1, "42sh", 4);
  write(1, RESET, strlen(RESET));
  write(1, " ", 1);
  write(1, GREEN, strlen(GREEN));
  write(1, shell->cwd, strlen(shell->cwd));
  write(1, RESET, strlen(RESET));
  write(1, " $> ", 4);
  if (shell->line)
    write(1, shell->line, strlen(shell->line));
}
