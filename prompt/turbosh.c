/*
** turbosh.c for turbosh in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 23:52:05 2017 Arthur Knoepflin
** Last update Fri May  5 00:11:57 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "my.h"

void	turbosh_prompt(t_shell *shell)
{
  my_putstr("##");
  my_printf("\033[32;1m%s\033[0m", getlogin());
  my_putstr(":");
  if (shell->current)
    my_printf("\033[34;1m%s\033[0m", shell->current);
  else
    my_printf("\033[34;1m?\033[0m");
  my_putstr("$ ");
}
