/*
** my_strcapitalize.c for my_strcapitalize in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:56:07 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:56:09 2017 Arthur Knoepflin
*/

char	*my_strcapitalize(char *str)
{
  int	count;

  count = 1;
  if (str[0] >= 97 && str[0] <= 122)
    str[0] = str[0] - 32;
  while (str[count] != '\0')
    {
      if (str[count] >= 'a' && str[count] <= 'z' &&
	  (str[count - 1] < 'A' || str[count - 1] > 'Z') &&
	  (str[count - 1] < 'a' || str[count - 1] > 'z') &&
	  (str[count - 1] < '0' || str[count - 1] > '9'))
        str[count] = str[count] - 32;
      else if ((str[count] >= 'A' && str[count] <= 'Z') &&
	       str[count - 1] != ' ')
	str[count] = str[count] + 32;
      count = count + 1;
    }
  return (str);
}
