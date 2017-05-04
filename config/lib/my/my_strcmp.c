/*
** my_strcmp.c for my_strcmp in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:56:55 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:56:55 2017 Arthur Knoepflin
*/

int	my_strcmp(char *str1, char *str2)
{
  int	i;

  i = 0;
  while (str1[i] && str2[i] && str1[i] == str2[i])
    i += 1;
  return (str1[i] - str2[i]);
}
