/*
** my_str_isprintable.c for my_str_isprintable in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:59:33 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:59:34 2017 Arthur Knoepflin
*/

int	my_str_isprintable(char *str)
{
  int	count;

  count = 0;
  while (str[count] != '\0')
    {
      if ((str[count] < 33 || str[count] > 126))
	return (0);
      count = count + 1;
    }
  return (1);
}
