/*
** io.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Tue Oct 18 16:47:42 2005 thomas moulard
** Last update Fri Nov 11 04:36:02 2005 thomas moulard
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

char	*getline(int fd)
{
  char	c = 0;
  int	size = 256;
  char	*res = NULL;
  int	pos = 0;

  if (!(res = malloc(size * sizeof (char))))
    return NULL;
  while ((read(fd, &c, 1)) != 0)
    {
      if (c == '\n')
	break;
      res[pos++] = c;
      if (pos >= size)
	  res = realloc(res, size += 256);
    }
  if (!pos && c != '\n')
    {
      free(res);
      return NULL;
    }
  res[pos] = 0;
  return res;
}
