/*
** my_putstr_fd.c for my_putstr_fd in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:53:55 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:53:56 2017 Arthur Knoepflin
*/

void	my_putstr_fd(char *str, int fd)
{
  int	i;

  i = -1;
  while (str[++i] != 0)
    my_putchar(str[i], fd);
}
