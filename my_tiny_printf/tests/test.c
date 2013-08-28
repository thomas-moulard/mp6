/*
** main.c for my_tiny_printf in /u/a1/moular_t/rendu/moular_t-mp6/my_tiny_printf/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Tue Nov  8 22:22:48 2005 thomas moulard
** Last update Fri Nov 11 19:19:44 2005 thomas moulard
*/

#include <stdio.h>
#include <limits.h>
#include "../src/tiny_printf.h"

int	main(void)
{
  int	res = 0;

  res = my_tiny_printf("toto %%\n");
  if (res != printf("toto %%\n"))
    return 1;
  res = my_tiny_printf("toto %");
  if (res != 6)
    return 2;
  res = my_tiny_printf("toto %d\n", '*');
  if (res != printf("toto %d\n", '*'))
    return 3;

  res = my_tiny_printf("toto %d\n", -12);
  if (res != printf("toto %d\n", -12))
    return 35;

  res = my_tiny_printf("toto %u\n", 321);
  if (res != printf("toto %u\n", 321))
    return 4;
  res = my_tiny_printf("toto %s\n", "12345");
  if (res != printf("toto %s\n", "12345"))
    return 5;
  res = my_tiny_printf("toto %c\n", '*');
  if (res != printf("toto %c\n", '*'))
    return 6;
  res = my_tiny_printf("toto %o\n", 42);
  if (res != printf("toto %o\n", 42))
    return 7;
  res = my_tiny_printf("toto %x\n", 42);
  if (res != printf("toto %x\n", 42))
    return 8;
  res = my_tiny_printf("toto %%%t\n");
  if (res != 8)
    return 9;
  res = my_tiny_printf("toto %t\n");
  if (res != 7)
    return 10;
  res = my_tiny_printf("toto %d\n", INT_MIN);
  if (res != printf("toto %d\n", INT_MIN))
    {
      printf("ERREUR %d %d\n", res, printf("toto %d\n", INT_MIN));
      return 11;
    }
  res = my_tiny_printf("toto %d\n", INT_MAX);
  if (res != printf("toto %d\n", INT_MAX))
    return 12;
  res = my_tiny_printf("toto %u\n", UINT_MAX);
  if (res != printf("toto %u\n", UINT_MAX))
    return 13;
  res = my_tiny_printf("toto %o\n", UINT_MAX);
  if (res != printf("toto %o\n", UINT_MAX))
    return 14;
  res = my_tiny_printf("toto %x\n", UINT_MAX);
  if (res != printf("toto %x\n", UINT_MAX))
    return 15;
  res = my_tiny_printf("toto %s\n", NULL);
  if (res != 6)
    return 16;
  return 0;
}
