/*
** my_str_isupper.c for my_str_isupper in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:59:45 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:59:46 2017 Arthur Knoepflin
*/

int	my_str_isupper(char *str)
{
  int	count;

  count = 0;
  while (str[count] != '\0')
    {
      if ((str[count] < 65 || str[count] > 90))
	return (0);
      count = count + 1;
    }
  return (1);
}
