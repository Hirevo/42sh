/*
** is_prime.c for my_lib in /home/benjamin/Dropbox/func/
**
** Made by Benjamin
** Login   <benjamin.solca@epitech.eu>
**
** Started on  Sun Apr  2 19:35:31 2017 Benjamin
** Last update Sun Apr  2 20:52:21 2017 Benjamin
*/

int	is_prime(int nb)
{
  int	i;

  if (nb < 2)
    return (0);
  else if (nb == 2)
    return (1);
  else if (nb % 2 == 0)
    return (0);
  else
    {
      i = 3;
      while ((i * i) <= nb)
	{
	  if ((nb % i) == 0)
	    return (0);
	  i = i + 1;
	}
    }
  return (1);
}
