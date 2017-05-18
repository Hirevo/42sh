/*
** env.c for env in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May 18 11:01:26 2017 Arthur Knoepflin
** Last update Thu May 18 11:10:56 2017 Arthur Knoepflin
*/

#include "shell.h"
#include "my.h"

int	env_b(t_shell *shell, int args)
{
  int	i;

  if (args == 1)
    {
      i = 0;
      while (environ[i])
	{
	  my_printf("%s\n", environ[i]);
	  i += 1;
	}
    }
  else
    my_puterror("env: invalid number of arguments\n");
}
