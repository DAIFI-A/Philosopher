/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:45:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/06/25 02:24:38 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


int philo_init(t_philo *philo)
{
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * philo->share.number_of_philosophers);
	if (!philo)
		return(0);
	while (i < philo->share.number_of_philosophers)
	{
		philo[i].share = philo->share;
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].right_fork = philo->share.fork[i];
		if (i + 1 == philo->share.number_of_philosophers)
			philo[i].left_fork = philo->share.fork[0];
		else
			philo[i].left_fork = philo->share.fork[i + 1];
		i++;
	}
	return 0;
}

int	mutex(t_share *data)
{
	int		i;

	i = 0;
	t_philo *philo;
	data->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex)
		return 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * philo->share.number_of_philosophers);
	while (i < philo->share.number_of_philosophers)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return 0;
}

void	*rout(void *data)
{
	t_philo *dat = (t_philo *)data;
	pthread_mutex_lock(&dat->right_fork);
	puts("take right fork");
	pthread_mutex_lock(&dat->left_fork);
	puts("take left fork");
	puts("eating");
	pthread_mutex_unlock(&dat->right_fork);
	pthread_mutex_unlock(&dat->left_fork);
	return NULL;
}

void	thread_creation(t_philo *data, int res, int i)
{
	data->share.threads = malloc(sizeof(data->share.number_of_philosophers));
	// pthread_mutex_init(&data->right_fork, NULL);
	// pthread_mutex_init(&data->left_fork, NULL);
	if (data->id % 2 == res)
	{
		pthread_create(&data->share.threads[i], NULL, &rout, &data);
	}
	pthread_join(*(data->share.threads + i), NULL);
	usleep(20);
}

int make_philo(t_philo *data)
{
	int		i;

	i = 0;
	while (i < data->share.number_of_philosophers)
	{
		thread_creation(data, 0, i);
		i++;
	}
	usleep(20);
	i = 0;
	while (i < data->share.number_of_philosophers)
	{
		thread_creation(data, 1, i);
		i++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	check_args(argc, argv);
	philo->share.number_of_philosophers = ft_atoi(argv[1]);
	if (philo->share.number_of_philosophers == 0)
		return (0);
	philo->share.time_to_die = ft_atoi(argv[2]);
	philo->share.time_to_eat = ft_atoi(argv[3]);
	philo->share.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo->share.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (philo->share.number_of_times_each_philosopher_must_eat == 0)
			return (0);
	}
	philo_init(philo);
	make_philo(philo);
	return 0;
}
