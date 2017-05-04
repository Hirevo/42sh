/*
** my_strncmp.c for my_strncmp in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:00:50 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:00:51 2017 Arthur Knoepflin
*/

int	my_strncmp(char *str1, char *str2, int n)
{
  int	i;

  i = 0;
  while (i < n - 1 && str1[i] && str2[i] && str1[i] == str2[i])
    {
      i += 1;
    }
  return (str2[i] - str1[i]);
}
