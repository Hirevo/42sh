/*
** oh_my_zsh.c for oh_my_zsh in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 12 18:42:45 2017 Arthur Knoepflin
** Last update Fri May 12 23:33:42 2017 Nicolas Polomack
*/

#include <libgen.h>
#include "shell.h"
#include "my.h"

void	oh_my_zsh(t_shell *shell)
{
  if (shell->exit == 0)
    my_putstr("\033[32;1m");
  else
    my_putstr("\033[31;1m");
  my_putstr("→  ");
  my_putstr("\033[0m");
  my_printf("\033[36;1m%s\033[0m ", basename(shell->current));
}
