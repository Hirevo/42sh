/*
** main.c for main.c in /home/nicolaspolomack/bin
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sun Apr  2 21:26:42 2017 Nicolas Polomack
** Last update Sat Apr 22 17:51:55 2017 Nicolas Polomack
*/

#include <sys/ioctl.h>
#include <curses.h>
#include <termio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "my.h"
#include "get_next_line.h"

int		main(int ac, char **av)
{
  t_shell	shell;

  init(&shell);
  while (1)
    {
      shell.line = NULL;
      shell.w.cur = 0;
      init_prompt(&shell);
      prompt_line(&shell);
      if (shell.line)
	write(1, "\n", 1);
      if (!shell.line || !strcmp(shell.line, "exit"))
	break;
      system(shell.line);
      free(shell.line);
    }
  if (shell.tty)
    {
      write(1, "exit\n", 5);
      if (ioctl(0, TCSETA, &shell.w.oterm) == -1)
	handle_error("ioctl");
    }
  return (0);
}
