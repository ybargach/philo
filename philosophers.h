#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct	s_philo
{
	int	a;
	int	b;
	int	*c;
	int	id;
	int	left_fork;
	int	right_fork;
	int	philo;
	int	phi_die;
	int	die;
	int	eat;
	int	sleep;
	pthread_mutex_t	*fork;
}		t_philo;


#endif
