/*
** tiny_printf.c for my_tiny_printf in /u/a1/moular_t/rendu/moular_t-mp6/my_tiny_printf/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Tue Nov  8 22:21:43 2005 thomas moulard
** Last update Fri Nov 11 19:19:05 2005 thomas moulard
*/

#include "tiny_printf.h"

int	my_printnbr_positif(unsigned long n)
{
  long	i;
  char	c;
  long 	div;
  int	res = 0;

  div = 1;
  while (n / div >= 10)
      div *= 10;
  while (div > 0)
    {
      i = (n / div) % 10;
      c = '0' + i;
      write(STDOUT_FILENO, &c, 1);
      res++;
      div /= 10;
    }
  return res;
}

int	my_printnbr(int n)
{
  char	c;
  int	i;
  char	intmax[] = "2147483648";

  if (n == -0x7fffffff - 1)
    {
      c = '-';
      write(STDOUT_FILENO, &c, 1);
      for (i = 0; i < 10; i++ )
	write(STDOUT_FILENO, &intmax[i], 1);
      return 11;
    }
  if (n < 0)
    {
      c = '-';
      write(STDOUT_FILENO, &c, 1);
      return my_printnbr_positif(-n) + 1;
    }
  return my_printnbr_positif(n);
}

int		my_printstr(char *s)
{
  int		l = 0;

  if (!s)
    {
      write(STDOUT_FILENO, "(null)", 6);
      return 0;
    }
  while (s[l])
    ++l;
  write(STDOUT_FILENO, s, l);
  return l;
}

static int	mystrlen(char str[])
{
  int		i = 0;

  while (str[i])
    i++;
  return i;
}

int	valid_base(char base[])
{
  int	i;
  int	j;
  int	l;

  l = mystrlen(base);
  if (l < 1)
    return 0;
  for (i = 0; i < l; i++)
    {
      for (j = i + 1; j < l; j++)
	if (base[i] == base[j])
	  return 0;
      if (base[i] == '-')
	return 0;
    }
  return 1;
}

int		my_printnbr_base_positif(unsigned long n, char base[])
{
  long		i;
  char		c;
  unsigned long	div;
  unsigned long	lbase;
  long		res = 0;

  lbase = mystrlen(base);
  div = 1;
  while (n / div >= lbase)
    div *= lbase;
  while (div > 0)
    {
      i = (n / div) % lbase;
      c = base[i];
      write(STDOUT_FILENO, &c, 1);
      div /= lbase;
      res++;
    }
  return res;
}

static int	my_printchar(char c)
{
  write(STDOUT_FILENO, &c, 1);
  return 1;
}

static int	tiny_draw(const char *format, int *i, int *res, va_list *list)
{
  if (!format[(*i)++])
      return 1;
  if (format[*i] == 'd')
    *res += my_printnbr(va_arg(*list, int));
  else if (format[*i] == 'u')
    *res += my_printnbr_positif(va_arg(*list, unsigned));
  else if (format[*i] == 's')
    *res += my_printstr(va_arg(*list, char *));
  else if (format[*i] == 'c')
    *res += my_printchar(va_arg(*list, int));
  else if (format[*i] == 'o')
    *res += my_printnbr_base_positif(va_arg(*list, unsigned), "01234567");
  else if (format[*i] == 'x')
    *res += my_printnbr_base_positif(va_arg(*list, unsigned),
			    "0123456789abcdef");
  else if (format[*i] == '%')
    {
      write(STDOUT_FILENO, format + (*i), 1);
      (*res)++;
    }
  else
    {
      write(STDOUT_FILENO, "%", 1);
      write(STDOUT_FILENO, format + (*i), 1);
      (*res) += 1 + (!format[(*i) + 1]);
    }
  return 0;
}

int		my_tiny_printf(const char *format, ...)
{
  int		res = 0;
  int		i = 0;
  va_list	list;

  va_start(list, format);
  while (format[i])
    {
      if (format[i] != '%')
	{
	  write(STDOUT_FILENO, format + i, 1);
	  res++;
	}
      else
	if (tiny_draw(format, &i, &res, &list))
	  break;
      if (format[i])
	i++;
    }
  va_end(list);
  return res;
}
