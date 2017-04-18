/*
** actions.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 19:00:07 2017 Nicolas Polomack
** Last update Tue Apr 18 19:04:35 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <string.h>
#include "shell.h"

void	remove_char(t_shell *shell)
{
  int	c;

  if (!shell->line || !strlen(shell->line))
    return ;
  delete_char(&shell->line, shell->w.cur);
  if (shell->w.cur)
    shell->w.cur -= 1;
  if (shell->tty)
    {
      write(1, shell->w.backw, strlen(shell->w.backw));
      write(1, shell->line + shell->w.cur, strlen(shell->line + shell->w.cur));
      write(1, " ", 1);
      shell->w.cur -= 1;
      pos_cursor(shell);
      shell->w.cur += 1;
    }
}

void	add_char(t_shell *shell, char c)
{
  insert_char(&shell->line, c, shell->w.cur);
  if (shell->tty)
    {
      write(1, shell->line + shell->w.cur, strlen(shell->line + shell->w.cur));
      shell->w.cur += 1;
      pos_cursor(shell);
    }
  else
    shell->w.cur += 1;
}

void	pos_cursor(t_shell *shell)
{
  int	c;

  if (!shell->line)
    return ;
  c = strlen(shell->line) - shell->w.cur - 1;
  while (c-- >= 0)
    write(1, shell->w.backw, strlen(shell->w.backw));
}

void	move_cursor(t_shell *shell, char c)
{
  if (get_input() != '[')
    return ;
  c = get_input();
  if (c == 'A' || c == 'B')
    return ;
  else if (c == 'C' && shell->line &&
           shell->w.cur < strlen(shell->line))
    {
      shell->w.cur += 1;
      write(1, shell->w.forw, strlen(shell->w.forw));
    }
  else if (c == 'D' && shell->w.cur)
    {
      shell->w.cur -= 1;
      write(1, shell->w.backw, strlen(shell->w.backw));
    }
}

void	clear_term(t_shell *shell)
{
  if (shell->tty)
    {
      write(1, shell->w.clear, strlen(shell->w.clear));
      init_prompt(shell);
      pos_cursor(shell);
    }
}
