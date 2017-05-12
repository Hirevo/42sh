/*
** actions.c for 42sh in /home/nicolaspolomack/psu/2/PSU_2016_42sh
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Apr 18 19:00:07 2017 Nicolas Polomack
** Last update Fri May 12 23:01:25 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my.h"
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
      write(1, shell->line + shell->w.cur,
	    strlen(shell->line + shell->w.cur));
      write(1, " ", 1);
      shell->w.cur -= 1;
      pos_cursor(shell);
      shell->w.cur += 1;
    }
}

void	add_char(t_shell *shell, char c)
{
  insert_char_cur(&shell->line, c, shell->w.cur);
  if (shell->tty)
    {
      write(1, shell->line + shell->w.cur,
	    strlen(shell->line + shell->w.cur));
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
  char	*str;
  int	dir;

  buffer_seq(shell, &str, &dir, c);
  if (dir == 1)
    move_backw(shell);
  else if (dir == 2)
    move_forw(shell);
  else if (dir == 3)
    move_upw(shell);
  else if (dir == 4)
    move_downw(shell);
  else
    while (str[++dir])
      insert_char_cur(&shell->line, str[dir],
		      shell->line ? strlen(shell->line) : 0);
  free(str);
}

void	clear_term(t_shell *shell)
{
  if (shell->tty)
    {
      write(1, shell->w.clear, strlen(shell->w.clear));
      init_prompt(shell);
      if (shell->line)
	my_putstr(shell->line);
      pos_cursor(shell);
    }
}
