/*
** ntc.h for mp6 in ~/dev/mp6/ntc
**
** Made by (CUISSARD Vincent)
** Login   <cuissa_v@epita.fr>
**
** Started on  Fri Aug 26 13:00:49 2005 CUISSARD Vincent
** Last update Fri Nov 11 01:21:56 2005 thomas moulard
*/

#ifndef   __NTC_H__
# define  __NTC_H__

# define FIFO "/tmp/ntc.fifo"


# ifndef FIFO
#  error "FIFO preproc variable must be defined"
# endif

# define BUFFER_SIZE	5
# define MSG_SIZE	256

enum	e_thread
{
  E_FIFO,
  E_STDIN
};

void			ntc_init(void);
void			ntc_destroy(void);
void			ntc_set_line(const char *line, enum e_thread type);
char			**ntc_get_lines(void);

extern pthread_mutex_t	gl_memory_mtx;
extern pthread_mutex_t	gl_dialog_cnd_mtx;
extern pthread_cond_t	gl_dialog_cnd;
extern char		**gl_memory;
extern unsigned int	gl_memory_offset;

#endif /* !__NTC_H__ */
