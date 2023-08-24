#include "philosophers.h"

void	*rot()
{
	printf("is eating\n");
	return NULL;
}


// int	mainss(int ac, char **av)
// {
// 	pthread_t t1, t2;
// 	pthread_create(&t1, NULL, &rot, NULL);
// 	pthread_create(&t2, NULL, &rot, NULL);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// }

int	ft_atoi(char *str)
{
	int	a;
	int	res;

	a = 0;
	res = 0;
	if (str[a] == '+')
		a++;
	while (str[a] >= '0' && str[a] <= '9')
	{
		res = res * 10 + str[a] - '0';
		a++;
	}
	return (res);
}

int	is_digit(char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (str[a])
	{
		if (str[a] == '+')
		{
			b++;
			if (b != 0 && b != 1)
				return (-1);
		}
		else if (!(str[a] >= '0' && str[a] <= '9'))
				return (-1);
		a++;
	}
	return (0);
}

long	ft_get_time(void)
{
	struct timeval	timenow;
	long	time;
	gettimeofday(&timenow, NULL);
	// printf("here    %ld\n", timenow.tv_usec);
	time = timenow.tv_usec;
	return (time);
}

void	ft_usleep(int ms)
{
	long time;

	time = ft_get_time();
	usleep(ms * 900);
	while (ft_get_time() < time + ms)
		usleep(20);
}

void	ft_fork(t_philo *data)
{
	pthread_mutex_lock(data->left_fork);
	printf("%ld : %d is take first fork\n", data->last_time, data->id);
	pthread_mutex_lock(data->right_fork);
	printf("%ld : %d is take second fork\n", data->last_time, data->id);
}

void	ft_eat(t_philo *data)
{
	printf("%ld : %d is eating\n", data->last_time, data->id);
	ft_usleep(data->eat);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	data->last_time = data->last_time + data->eat;
}

void	ft_sleep(t_philo *data)
{
	ft_usleep(data->sleep);
	printf("%ld : %d is sleep\n", data->last_time, data->id);
	data->last_time = data->last_time + data->eat;
	printf("%ld : %d is thinking\n", data->last_time, data->id);
}

void	ft_die(t_philo *data)
{
	printf("%ld : %d is die\n", data->last_time, data->id);
	exit(0);
}

void	*routine(void *arg)
{
	t_philo *data = (t_philo *)arg;
	if (data->id % 2 == 0)
		ft_usleep(100);
	ft_fork(data);
	ft_eat(data);
	ft_sleep(data);
	return (NULL);
}

void	ft_copy(t_data *arr, t_philo *philo)
{
	philo->die = arr->die;
	philo->eat = arr->eat;
	philo->first_time = arr->first_time;
	philo->last_time = arr->last_time;
	philo->nbr_philo = arr->nbr_philo;
	philo->sleep = arr->sleep;
}

void	av_atoi(t_data *arr, int ac, char **av)
{
	arr->die = ft_atoi(av[2]);
	arr->eat = ft_atoi(av[3]);
	arr->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arr->think = ft_atoi(av[5]);
}

void	before_create(int ac, char **av)
{
	int	a;
	int	b;
	t_data	*arr;

	a = 0;
	b = 0;
	arr = (t_data *)malloc(sizeof(t_data));
	arr->nbr_philo = ft_atoi(av[1]);
	av_atoi(arr, ac, av);
	arr->philo = (t_philo *)malloc(arr->nbr_philo * sizeof(t_philo));
	arr->fork = (pthread_mutex_t *)malloc(arr->nbr_philo * sizeof(pthread_mutex_t));
	while (b < arr->nbr_philo)
	{
		pthread_mutex_init(&arr->fork[b], NULL);
		b++;
	}
	arr->first_time = ft_get_time();
	// arr->last_time = arr->first_time;
	ft_copy(arr, arr->philo);
	while (a < arr->nbr_philo)
	{
		arr->philo[a].last_time = ft_get_time() - arr->first_time;
	// printf("%ld\n", arr->philo[a].last_time);
	// exit(0);
		arr->philo[a].id = a + 1;
		arr->philo[a].left_fork = &arr->fork[a];
		arr->philo[a].right_fork = &arr->fork[(a + 1) % arr->nbr_philo];
		pthread_create(&arr->philo[a].thread, NULL, routine, &arr->philo[a]);
		pthread_detach(arr->philo[a].thread);
		a++;
	}
}

int	check_argv(char **av)
{
	int	a;

	a = 1;
	while (av[a])
	{
		if (is_digit(av[a]) == -1)
			return (1);
		a++;
	}
	return (0);
}

int	error_argv(void)
{
	printf("error in argv\n");
	return (1);
}

int	main(int ac, char **av)
{
	if (!(ac >= 5 && ac <= 6) || check_argv(av) == 1)
		return (error_argv());
	before_create(ac, av);
	sleep(1);
	return (0);
}
