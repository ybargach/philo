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

// void	up_forks(t_philo *arr)
// {
// 	arr->left_fork = arr->a;
// 	//arr->right_fork = (arr->a + 1) % arr->philo;
// 	pthread_mutex_lock(&arr->fork[arr->left_fork]);
// 	//pthread_mutex_lock(&arr->fork[arr->right_fork]);
// }

// void	down_forks(t_philo *arr)
// {
// 	arr->left_fork = arr->a;
// 	//arr->right_fork = (arr->a + 1) % arr->philo;
// 	pthread_mutex_unlock(&arr->fork[arr->right_fork]);
// 	//pthread_mutex_unlock(&arr->fork[arr->left_fork]);
// }

void	*create_thread(void *arg)
{
	t_philo *arr = (t_philo *)arg;
	//pthread_mutex_t	fork;
	pthread_mutex_lock(&arr->fork[arr->a]);
	//up_forks(arr);
	// rot();
	arr->id =  *arr->c + 1;
	printf("%d\n", arr->id);
	sleep(1);
	pthread_mutex_unlock(&arr->fork[arr->a]);
	//down_forks(arr);
	// sleep;
	// think;

	//free(arr->c);
	return (NULL);
}

void	before_create(int ac, char **av, t_philo *arr)
{
	pthread_t	*th;

	arr->a = 0;
	arr->b = 0;
	arr->philo = ft_atoi(av[1]);
	arr->die = ft_atoi(av[2]);
	arr->eat = ft_atoi(av[3]);
	arr->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arr->phi_die = ft_atoi(av[5]);
	th = malloc(arr->philo * sizeof(pthread_t));
	arr->fork = malloc(arr->philo * sizeof(pthread_mutex_t));
	while (arr->b < arr->philo)
	{
		pthread_mutex_init(&arr->fork[arr->b], NULL);
		arr->b++;
	}
	while (arr->a < arr->philo)
	{
		arr->c = malloc(sizeof(int));
		*arr->c = arr->a;
		pthread_create(&th[arr->a], NULL, create_thread, arr);
		arr->a++;
	}
}

int	check_argv(char **av, t_philo *arr)
{
	arr->a = 1;
	while (av[arr->a])
	{
		if (is_digit(av[arr->a]) == -1)
			return (1);
		arr->a++;
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
	t_philo	*arr;

	arr = (t_philo *)malloc(sizeof(t_philo));
	if (!(ac >= 5 && ac <= 6) || check_argv(av, arr) == 1)
		return (error_argv());
	{
	before_create(ac, av, arr);
		//exit(0);
	}
	while(1);
	return (0);
}
