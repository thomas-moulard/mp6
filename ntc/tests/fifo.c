/*
** fifo.c for NTC in /u/a1/moular_t/rendu/moular_t-mp6/ntc/tests
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Thu Nov 10 16:13:54 2005 thomas moulard
** Last update Fri Nov 11 15:14:42 2005 thomas moulard
*/

#define FIFO "/tmp/ntc.fifo"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/main.h"

int	my_strlen(char *s)
{
  int	i = 0;

  while (s[i])
    i++;
  return i;
}

int	main(void)
{
  int	fd = 0;
  char	*c = NULL;

  fd = open(FIFO, O_WRONLY);
  if (!fd)
    {
      write(STDERR_FILENO, "Unable to open fifo\n", 20);
      return 0;
    }
  while ((c = getline(STDIN_FILENO)))
  {
    write(fd, c, my_strlen(c));
    write(fd, "\n", 1);
    free(c);
  }
  close(fd);
  printf("FIFO ferme.\n");
  return 0;
}
