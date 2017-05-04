/*
** my_strncat.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 20:39:38 2017 Benjamin
** Last update Sun Apr  2 20:39:41 2017 Benjamin
*/

char	*my_strncat(char *dest, char *src, int nb)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (dest[i] != '\0' && i < nb)
    {
      i++;
    }
  while (src[j] != '\0')
    {
      dest[i] = src[j];
      i++;
      j++;
    }
  return (dest);
}
