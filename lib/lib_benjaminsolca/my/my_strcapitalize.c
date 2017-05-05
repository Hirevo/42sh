/*
** my_strcapitalize.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 20:15:59 2017 Benjamin
** Last update Sun Apr  2 20:37:25 2017 Benjamin
*/

char	*my_strcapitalize(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 'a' && str[i] <= 'z')
	str[i] = str[i] - 32;
      if ((str[i - 1] >= 'A' && str[i - 1] <= 'Z') ||
	  (str[i - 1] >= 'a' && str[i - 1] <= 'z') ||
	  (str[i - 1] >= '0' && str[i - 1] <= '9'))
	if (str[i] >= 'A' && str[i] <= 'Z')
	  str[i] = str[i] + 32;
      i++;
    }
  return (str);
}
