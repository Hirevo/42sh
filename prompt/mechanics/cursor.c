/*
** cursor.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Apr 22 17:04:32 2017 Nicolas Polomack
** Last update Fri May  5 06:27:32 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <string.h>
#include "shell.h"

void	buffer_seq(t_shell *shell, char **str, int *dir, char c)
{
  *str = NULL;
  *dir = -1;
  insert_char_cur(str, c, 0);
  while (strstr(shell->w.left, *str) ||
         strstr(shell->w.right, *str))
    {
      while (!(c = get_input()));
      insert_char_cur(str, c, strlen(*str));
      if (!strcmp(*str, shell->w.left))
        {
          *dir = 1;
          break;
        }
      else if (!strcmp(*str, shell->w.right))
	{
          *dir = 2;
          break;
        }
    }
}

void	move_forw(t_shell *shell)
{
  if (shell->line &&
      shell->w.cur < strlen(shell->line))
    {
      shell->w.cur += 1;
      write(1, shell->w.forw, strlen(shell->w.forw));
    }
}

void	move_backw(t_shell *shell)
{
  if (shell->w.cur)
    {
      shell->w.cur -= 1;
      write(1, shell->w.backw, strlen(shell->w.backw));
    }
}
