/*
** ntc_extern.c for mp6 in /
**
** Made by (CUISSARD Vincent)
** Login   <cuissa_v@epita.fr>
**
** Started on  Fri Aug 26 13:26:48 2005 CUISSARD Vincent
** Last update Mon Nov  7 17:41:55 2005 CUISSARD Vincent
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ntc.h"

pthread_mutex_t	gl_memory_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	gl_dialog_cnd_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	gl_dialog_cnd = PTHREAD_COND_INITIALIZER;
char		**gl_memory;
unsigned int	gl_memory_offset;

void		ntc_init(void)
{
  int		i;

  gl_memory_offset = 0;
  gl_memory = calloc(MSG_SIZE, sizeof (char *));
  for (i = 0; i < MSG_SIZE; ++i)
    gl_memory[i] = calloc(MSG_SIZE + 7, sizeof (char));
}

void		ntc_destroy(void)
{
  int		i;

  for (i = 0; i < MSG_SIZE; ++i)
    free(gl_memory[i]);
  free(gl_memory);
}

void		ntc_set_line(const char *line, enum e_thread type)
{
  static char	dialog = 1;

  sprintf(gl_memory[gl_memory_offset], "%s> %s",
	  type == E_FIFO ? " fifo" : "stdin", line);
  ++gl_memory_offset;
  if (dialog % BUFFER_SIZE != 0)
    ++dialog;
  else
  {
    dialog = 1;
    pthread_mutex_lock(&gl_dialog_cnd_mtx);
    {
      pthread_cond_signal(&gl_dialog_cnd);
    }
    pthread_mutex_unlock(&gl_dialog_cnd_mtx);
  }
}

char            **ntc_get_lines(void)
{
  char		**lines;
  int		i;

  lines = calloc(BUFFER_SIZE, sizeof (char *));
  for (i = 0; i < BUFFER_SIZE; ++i)
  {
    lines[i] = calloc(MSG_SIZE + 7, 1);
    strcpy(lines[i], gl_memory[gl_memory_offset - BUFFER_SIZE + i]);
  }
  return lines;
}

