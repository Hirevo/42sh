/*
** launch_config.c for launch_config in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 20:40:56 2017 Arthur Knoepflin
** Last update Fri May 12 22:45:09 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "shell.h"
#include "server.h"
#include "get_next_line.h"

int		launch_config(t_shell *shell)
{
  int		ret;
  char		*prompt;
  t_config	config;

  config.env = environ;
  config.prompt = shell->prompt;
  ret = config_http(&config);
  shell->prompt = config.prompt;
  asprintf(&prompt, "%d", config.prompt);
  setenv("PROMPT", prompt, 1);
  free(prompt);
  return (ret);
}
