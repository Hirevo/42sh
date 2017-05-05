/*
** my_strncmp.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 20:40:56 2017 Benjamin
** Last update Thu Apr  6 14:22:26 2017 Benjamin
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  i = 0;
  while (s1[i] && s2[i] ? s1[i] == s2[i] && i < (n - 1) : 0)
    {
      i = i + 1;
    }
  return (s1[i] - s2[i]);
}
