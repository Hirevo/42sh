/*
** my_strupcase.c for my_strupcase in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:02:43 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:02:44 2017 Arthur Knoepflin
*/

char	*my_strupcase(char *str)
{
  int	count;

  count = 0;
  while (str[count] != '\0')
    {
      if (str[count] >= 97 && str[count] <= 122)
	str[count] = str[count] - 32;
      count = count + 1;
    }
  return (str);
}
