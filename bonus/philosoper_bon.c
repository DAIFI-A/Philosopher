# include "philo_bonus.h"

t_philo *philo_init(t_share	*share)
{
	t_philo		*philo;
	int			i;
	
	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * share->number_of_philosophers);
	if (!philo)
		return(NULL);
	while (++i < share->number_of_philosophers)
	{
		philo[i].process_id = i + 1;
		philo[i].share = share;
		philo[i].n = share->number_of_philosophers;
		philo[i].id = i + 1;
		//philo[i].last_eat_time = ft_get_time();
		philo[i].flage = 0;
		philo[i].count_meal = 0;
		philo[i].nbr_meals = share->number_of_meals;
		philo[i].time_to_die = share->time_to_die;
		philo[i].time_to_eat = share->time_to_eat;
		philo[i].time_to_sleep = share->time_to_sleep;
	}
	return (philo);
}

void	routine(t_philo *philo, sem_t *mutex)
{
	while (!philo->share->flage)
		tasks(philo, mutex);
	sem_close(mutex);
}

void	create_thread(t_philo *philo, sem_t *mutex)
{
	philo->share->start_t = ft_get_time();
	philo->last_eat_time = philo->share->start_t;
	pthread_create(&philo->death, NULL, &check_death, philo);
	while (!philo->share->flage)
		routine(philo, mutex);
	if (philo->flage == 1)
		exit(0);
	exit(0);
}

int	thread_init(t_philo *p)
{
	int			i;
	sem_t		*mutex;

	i = -1;
	sem_unlink("mutex");
	mutex = sem_open("mutex", O_CREAT, 666, p->share->number_of_philosophers);
	while (++i < p->share->number_of_philosophers)
	{
		p[i].process = fork();
		if (p[i].process < 0)
			exit(0);
		else if (p[i].process == 0)
			create_thread(&p[i], mutex);
	}
	return (0);
}

void	check_stat(t_philo *philo, t_share *share)
{
	int	i;
	int	status;

	i = 0;
	status = -1;
	while (i < share->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			i = 0;
			while (i < share->number_of_philosophers)
			{
				kill(philo[i].process, SIGKILL);
				i++;
			}
			printf("%u %d died\n", ft_get_time() -  philo->share->start_t, philo->process_id);
			exit(0);
		}
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_share	*share;;
	t_philo	*philo;
	int			i;

	if (ac != 5 && ac != 6)
		return (write(1, "ERROR\n", 6));
	share = (t_share *)malloc(sizeof(t_share));
	check_args(ac, av);
	share->flage = 0;
	share->number_of_philosophers = ft_atoi(av[1]);
	if (share->number_of_philosophers == 0)
		return (0);
	share->time_to_die = ft_atoi(av[2]);
	share->time_to_eat = ft_atoi(av[3]);
	share->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		share->number_of_meals = ft_atoi(av[5]);
		if (share->number_of_meals == 0)
			return (0);
	}
	else 
		share->number_of_meals = -1;
	philo = philo_init(share);
	thread_init(philo);
	check_stat(philo, share);
	sem_unlink("mutex");
	return (0);
}