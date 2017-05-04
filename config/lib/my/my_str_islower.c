/*
** my_str_islower.c for my_str_islower in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:58:05 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:58:08 2017 Arthur Knoepflin
*/

int	my_str_islower(char *str)
{
  int	count;

  count = 0;
  while (str[count] != '\0')
    {
      if ((str[count] < 97 || str[count] > 122))
	return (0);
      count = count + 1;
    }
  return (1);
}
