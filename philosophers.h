#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct s_philo
{
	int			id;
	int			nbr_philo;
	int			sleep;
	int			eat;
	int			think;
	int			die;
	int			r_fork;
	int			l_fork;
	long		last_time;
	long		first_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t	thread;
}		t_philo;


typedef struct	s_data
{
	int	id;
	int	nbr_philo;
	int	think;
	int	die;
	int	eat;
	int	sleep;
	long	last_time;
	long	first_time;
	pthread_mutex_t	*fork;
	t_philo	*philo;
}	t_data;


#endif
