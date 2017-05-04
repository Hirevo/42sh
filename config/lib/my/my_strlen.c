/*
** my_strlen.c for my_strlen in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:00:00 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:00:01 2017 Arthur Knoepflin
*/

int	my_strlen(char *str)
{
  int	count;

  count = 0;
  while (str[count] != 0)
    count = count + 1;
  return (count);
}
