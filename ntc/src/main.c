/*
** main.c for NTC in /u/a1/moular_t/rendu/moular_t-mp6/ntc/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Thu Nov 10 15:36:20 2005 thomas moulard
** Last update Fri Nov 11 15:27:26 2005 thomas moulard
*/
#include "main.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	*threadA(void *attr)
{
  char		*str = NULL;
  int		*fifo = attr;

  while ((str = getline(STDIN_FILENO)))
    {
      pthread_mutex_lock(&gl_memory_mtx);
      {
	ntc_set_line(str, E_STDIN);
      }
      pthread_mutex_unlock(&gl_memory_mtx);
      free(str);
    }
  close(*fifo);
  ntc_destroy();
  exit(0);
  pthread_exit(NULL);
  return NULL;
}

static void	*threadB(void *attr)
{
  int		*fifo = attr;
  char		*str = NULL;

  if (!(*fifo = open(FIFO, O_RDONLY)))
    {
      write(STDERR_FILENO, "Unable to open fifo.\n", 21);
      exit(1);
    }
  while (1)
    {
      str = getline(*fifo);
      pthread_mutex_lock(&gl_memory_mtx);
      ntc_set_line(str, E_FIFO);
      pthread_mutex_unlock(&gl_memory_mtx);
      free(str);
    }
  pthread_exit(NULL);
  return NULL;
}

static void	*threadC(void *attr)
{
  char		**buffer;
  int		i = 0;
  int		j = 0;

  attr = attr;
  while (1)
    {
      pthread_mutex_lock(&gl_dialog_cnd_mtx);
      pthread_cond_wait(&gl_dialog_cnd, &gl_dialog_cnd_mtx);
      pthread_mutex_unlock(&gl_dialog_cnd_mtx);
      pthread_mutex_lock(&gl_memory_mtx);
      buffer = ntc_get_lines();
      write(STDOUT_FILENO, "[ BUFFER ]\n", 11);
      for (i = 0; i < BUFFER_SIZE; i++)
	{
	  j = 0;
	  while (buffer[i][j])
	    j++;
	  write(STDOUT_FILENO, "  ", 2);
	  write(STDOUT_FILENO, buffer[i], j);
	  write(STDOUT_FILENO, "\n", 1);
	}
      pthread_mutex_unlock(&gl_memory_mtx);
      write(STDOUT_FILENO, "[ ENDBUFFER ]\n", 14);
    }
  return NULL;
}

int		main(void)
{
  pthread_t	tA;
  pthread_t	tB;
  pthread_t	tC;
  int		fifo = 0;

  ntc_init();
  mkfifo(FIFO, S_IRWXU);
  if (0 != (pthread_create(&tA, NULL, threadA, &fifo)))
    {
      write(STDERR_FILENO, "Unable to create thread A.\n", 27);
      return 1;
    }
  if (0 != (pthread_create(&tB, NULL, threadB, &fifo)))
    {
      write(STDERR_FILENO, "Unable to create thread B.\n", 27);
      return 1;
    }
  if (0 != (pthread_create(&tC, NULL, threadC, NULL)))
    {
      write(STDERR_FILENO, "Unable to create thread C.\n", 27);
      return 1;
    }
  pthread_join(tA, NULL);
  pthread_join(tB, NULL);
  pthread_join(tC, NULL);
  return 0;
}
