/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:45:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/06/25 22:35:23 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"


t_philo *philo_init(t_share	*share)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * share->number_of_philosophers);
	if (!philo)
		return(NULL);
	while (i < share->number_of_philosophers)
	{
		philo[i].share = share;
		philo[i].id = i + 1;
		philo[i].last_meal = -1;
		philo[i].right_fork = &(share->fork[i]);
		if (i + 1 == share->number_of_philosophers)
			philo[i].left_fork = &(share->fork[0]);
		else
			philo[i].left_fork = &(share->fork[i + 1]);
		i++;
	}
	return (philo);
}

int	mutex(t_share *data)
{
	int		i;

	i = 0;
	t_philo *philo;
	data->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex)
		return 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * philo->share->number_of_philosophers);
	while (i < philo->share->number_of_philosophers)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return 0;
}

void	*rout(void *data)
{
	t_philo *dat = (t_philo *)data;
	pthread_mutex_lock(dat->right_fork);
	printf("%d  take right fork\n", dat->id);
	pthread_mutex_lock(dat->left_fork);
	printf("%d take left fork\n", dat->id);
	printf("%d eating\n", dat->id);
	pthread_mutex_unlock(dat->right_fork);
	pthread_mutex_unlock(dat->left_fork);
	return NULL;
}

void	thread_creation(t_philo *data, int res, int i)
{
	data->share->threads = malloc(sizeof(pthread_t) * data->share->number_of_philosophers);
	if (data[i].id % 2 == res)
	{
		pthread_create(&data->share->threads[i], NULL, &rout, &data->share->threads[i]);
	}
	usleep(20);
}

int make_philo(t_philo *data)
{
	int		i;

	i = 0;
	while (i < data->share->number_of_philosophers)
	{
		thread_creation(data, 0, i);
		i++;
	}
	usleep(20);
	i = 0;
	while (i < data->share->number_of_philosophers)
	{
		thread_creation(data, 1, i);
		i++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_share	*share;
	t_philo	*philo;

	share = (t_share *)malloc(sizeof(t_share));
	check_args(argc, argv);
	share->number_of_philosophers = ft_atoi(argv[1]);
	if (share->number_of_philosophers == 0)
		return (0);
	share->time_to_die = ft_atoi(argv[2]);
	share->time_to_eat = ft_atoi(argv[3]);
	share->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		share->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (share->number_of_times_each_philosopher_must_eat == 0)
			return (0);
	}
	philo = philo_init(share);
	make_philo(philo);
	return 0;
}
