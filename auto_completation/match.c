/*
** match.c for match in /home/arthur/delivery/CPool_match-nmatch/
**
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
**
** Started on  Sat Oct 15 18:43:19 2016 Arthur Knoepflin
** Last update	Tue May 09 13:51:02 2017 Full Name
*/

int	match(char *s1, char *s2)
{
  int	ret;

  if (*s1 == '\0' && *s2 == '\0')
    return (1);
  else if (*s2 == '*' && *s1 == '\0')
    ret = match(s1, s2 + 1);
  else if (*s2 == '*')
    ret = (match(s1, s2 + 1) || match(s1 + 1, s2));
  else if (*s1 == *s2)
    ret = match(s1 + 1, s2 + 1);
  else
    return (0);
  return (ret);
}
