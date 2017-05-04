/*
** my_power_rec.c for my_power_rec in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 22:51:19 2017 Arthur Knoepflin
** Last update Sat Mar 25 22:51:20 2017 Arthur Knoepflin
*/

int	my_power_rec(int nb, int p)
{
  int	resp_power_rec;

  resp_power_rec = 1;
  if (p == 0)
    {
      return (resp_power_rec);
    }
  else if (p < 0)
    {
      return (0);
    }
  else
    {
      resp_power_rec = nb;
      resp_power_rec = resp_power_rec * my_power_rec(nb, p - 1);
      return (resp_power_rec);
    }
}
