/*
** cd.c for cd in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 16 01:44:21 2017 Arthur Knoepflin
** Last update Tue May 16 01:46:23 2017 Arthur Knoepflin
*/

#include "shell.h"

int	cd_b(t_shell *shell, int args)
{
  return (move_dir(shell->cur->av, args, shell));
}
