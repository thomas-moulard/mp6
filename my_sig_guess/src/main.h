/*
** main.h for my_sig_guess in /u/a1/moular_t/rendu/moular_t-mp6/my_sig_guess/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Fri Nov 11 00:10:01 2005 thomas moulard
** Last update Fri Nov 11 00:11:24 2005 thomas moulard
*/

#ifndef MAIN_H_
# define MAIN_H_
# include <unistd.h>
# include <signal.h>
# include <stdio.h>

struct				s_sig_guess
{
  char				n_bit;
  unsigned char			number;
  sigset_t			old;
  sigset_t			new;
};

extern struct s_sig_guess	gl_guess;

#endif /* !MAIN_H_ */
