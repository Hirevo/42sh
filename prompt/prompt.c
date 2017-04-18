/*
** prompt.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 19:05:01 2017 Nicolas Polomack
** Last update Tue Apr 18 19:11:10 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <string.h>
#include "shell.h"

void	prompt_line(t_shell *shell)
{
  char  c;

  c = -1;
  while (c != 10)
    {
      if ((c = get_input()) == -1)
        if (shell->tty)
          continue ;
        else
          return ;
      if (c == 10 && !shell->line)
        shell->line = strdup("");
      if (c == 0 || c == 4)
        write(1, "\n", 1);
      if (c == 10 || c == 0 || c == 4 ||
          (c == -2 && !shell->tty))
        break;
      if (c == 12)
        clear_term(shell);
      else if (c == 127)
        remove_char(shell);
      else if (c == 27)
        move_cursor(shell, c);
      else
        add_char(shell, c);
    }
}
