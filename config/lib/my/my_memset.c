/*
** my_memset.c for my_memset in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:51:03 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:51:04 2017 Arthur Knoepflin
*/

void	*my_memset(void *str, int c, int size)
{
  char	*tmp;

  if (size)
    {
      size += 1;
      tmp = str;
      while (--size)
	{
	  *tmp++ = c;
	}
    }
  return (str);
}
