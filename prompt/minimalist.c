/*
** minimalist.c for minimalist in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May  5 00:50:04 2017 Arthur Knoepflin
** Last update Fri May  5 01:39:52 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "my.h"

void	minimalist_prompt(t_shell *shell)
{
  char	*user;

  if ((user = getenv("LOGNAME")))
    my_printf("%s) ", user);
  else
    my_putstr(") ");
}
