/*
** main.c for my_sig_guess in /u/a1/moular_t/rendu/moular_t-mp6/my_sig_guess/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Tue Nov  8 00:06:51 2005 thomas moulard
** Last update Fri Nov 11 15:58:14 2005 thomas moulard
*/

#include "main.h"

struct s_sig_guess	gl_guess;

void			hdl_sigusr1(int sig)
{
  sig = sig;
  gl_guess.n_bit++;
  gl_guess.number = gl_guess.number * 2;
}

void			hdl_sigusr2(int sig)
{
  sig = sig;
  gl_guess.n_bit++;
  gl_guess.number = gl_guess.number * 2 + 1;
}

static void		my_printnbr(int n)
{
  long			i;
  char			c;
  long			div;

  div = 1;
  while (n / div >= 10)
      div *= 10;
  while (div > 0)
    {
      i = (n / div) % 10;
      c = '0' + i;
      write(STDOUT_FILENO, &c, 1);
      div /= 10;
    }
}

static int		getint()
{
  int		res = 0;
  char		c;

  while (read(STDIN_FILENO, &c, 1))
    {
      if ((c < '0' || c > '9') && (c != 0) && (c != '\n') && (c != '\t'))
	res = -1;
      if (!c || c == '\n')
	break;
      if (c == ' ' || c == '\t')
	continue;
      if (res >= 0)
	res = res * 10 + c - '0';
    }
  return res;
}

static void		init(void)
{
  struct sigaction	sa;
  struct sigaction	sa2;

  gl_guess.n_bit = gl_guess.number = 0;
  sa.sa_handler = hdl_sigusr1;
  sa.sa_flags = 0;
  if (sigaction(SIGUSR1, &sa, NULL) == -1)
    perror("Can't redefine signal handler.");
  sa2.sa_handler = hdl_sigusr2;
  sa2.sa_flags = 0;
  if (sigaction(SIGUSR2, &sa2, NULL) == -1)
    perror("Can't redefine signal handler.");

  sigaddset(&gl_guess.new, SIGUSR1);
  sigaddset(&gl_guess.new, SIGUSR2);
  sigprocmask(SIG_BLOCK, &gl_guess.new, &gl_guess.old);
  write(STDOUT_FILENO, "PID: ", 5);
  my_printnbr(getpid());
}

static void		send_bit(unsigned char n, int pid, int wait)
{
  gl_guess.number = 0;
  if (n == 0)
    kill(pid, SIGUSR1);
  else
    kill(pid, SIGUSR2);
  if (wait)
    sigsuspend(&gl_guess.old);
}

void			send_int(unsigned n, int pid)
{
  int			l = 8;

  write(STDOUT_FILENO, "Sending integer to server... ", 29);
  gl_guess.n_bit = gl_guess.number = 0;
  while (n > 0)
    {
      send_bit(n % 2, pid, l >= 2);
      l--;
      n /= 2;
    }
  gl_guess.number = 0;
  while (l >= 2)
    {
      send_bit(0, pid,  1);
      l--;
    }
  if (l)
    send_bit(0, pid, 0);
  write(STDOUT_FILENO, "OK\n", 3);
}

static void		receive_bit(int pid, int ack)
{
  sigsuspend(&gl_guess.old);
  if (ack)
    kill(pid, SIGUSR1);
}

int			receive_int(int pid)
{
  gl_guess.n_bit = gl_guess.number = 0;
  write(STDOUT_FILENO, "Receiving response from server... ", 34);
  receive_bit(pid, 1);
  receive_bit(pid, 0);
  write(STDOUT_FILENO, "OK\n", 3);
  return gl_guess.number;;
}

int			main(void)
{
  int		pid;
  int		n = 0;

  init();
  write(STDOUT_FILENO, "\nPID du serveur: ", 17);
  pid = getint();
  while (n != 3)
    {
      do
	{
	  write(STDOUT_FILENO, "Number? ", 8);
	  if ((n = getint()) > 255)
	    n = -1;
	}
      while (n == -1);
      send_int(n, pid);
      n = receive_int(pid);
      if (n == 1)
	write(STDOUT_FILENO, "Too low!\n", 9);
      else if (n == 2)
	write(STDOUT_FILENO, "Too high!\n", 10);
      else if (n == 3)
	write(STDOUT_FILENO, "Correct number\n", 15);
      write(STDOUT_FILENO, "\n\n", 2);
    }
  return 0;
}
