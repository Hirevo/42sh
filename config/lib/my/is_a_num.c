/*
** is_a_num.c for is_a_num.c in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:40:18 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:40:20 2017 Arthur Knoepflin
*/

int	is_a_num(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (0);
      i += 1;
    }
  return (1);
}
