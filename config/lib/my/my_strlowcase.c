/*
** my_strlowcase.c for my_strlowcase in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:00:17 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:00:17 2017 Arthur Knoepflin
*/

char	*my_strlowcase(char *str)
{
  int	count;

  count = -1;
  while (str[++count] != 0)
    if (str[count] >= 'A' && str[count] <= 'Z')
      str[count] = str[count] + 32;
  return (str);
}
