/*
** is_in.c for is_in in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:36:58 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:38:37 2017 Arthur Knoepflin
*/

int	is_in(char *str, char c)
{
  int	i;

  i = -1;
  while (str[++i])
    if (str[i] == c)
      return (1);
  return (0);
}
