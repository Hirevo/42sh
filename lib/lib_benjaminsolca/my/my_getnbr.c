/*
** my_getnbr.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:34:59 2017 Benjamin
** Last update Sun Apr  2 19:44:02 2017 Benjamin
*/

int	my_getnbr(char *str)
{
  int	i;
  int	calc_min;
  long	calc;

  i = 0;
  calc_min = 1;
  calc = 0;
  while ((str[i] == '-' || str[i] == '+') && str[i] != '\0')
    {
      if (str[i] == '-')
	calc_min = calc_min * -1;
      i++;
    }
  while (str[i] >= '0' && str[i] <= '9')
    {
      calc = (str[i] - 48) + (calc * 10);
      i++;
    }
  if (calc > 2147483647 || (calc * calc_min) < -2147483648)
    return (0);
  return (calc * calc_min);
}
