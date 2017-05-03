/*
** my_strcmp.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 20:37:59 2017 Benjamin
** Last update Sun Apr  2 20:38:02 2017 Benjamin
*/

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i] == s2[i] && s1[i] != '\0')
      i = i + 1;

  return (s1[i] - s2[i]);
}
