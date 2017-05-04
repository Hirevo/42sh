/*
** my_str_isnum.c for my_str_isnum in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:58:38 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:58:39 2017 Arthur Knoepflin
*/

int	my_str_isnum(char *str)
{
  int	count;

  count = 0;
  while (str[count] != 0)
    {
      if ((str[count] == '-' && count != 0) ||
      	(str[count] < '0' || str[count] > '9'))
	return (0);
      count += 1;
    }
  return (1);
}
