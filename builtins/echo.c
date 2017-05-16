/*
** echo.c for echo in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 01:56:34 2017 Arthur Knoepflin
** Last update Tue May 16 01:57:46 2017 Arthur Knoepflin
*/

#include "shell.h"

int	echo_b(t_shell *shell, int args)
{
  (void) args;
  echo_term(shell->cur->av + 1);
}
