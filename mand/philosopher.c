/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:45:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 22:58:39 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include<pthread.h>

t_philo	*philo_init(t_share	*share, t_philo *philo)
{
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * share->number_of_philosophers);
	if (!philo)
		return (NULL);
	while (++i < share->number_of_philosophers)
	{
		philo[i].share = share;
		philo[i].n = share->number_of_philosophers;
		philo[i].id = i + 1;
		philo[i].last_meal = -1;
		philo[i].flage = 0;
		philo[i].count_meal = 0;
		philo[i].nbr_meals = share->number_of_meals;
		philo[i].time_to_die = share->time_to_die;
		philo[i].time_to_eat = share->time_to_eat;
		philo[i].time_to_sleep = share->time_to_sleep;
		philo[i].right_fork = &(share->fork[i]);
		if (i + 1 == share->number_of_philosophers)
			philo[i].left_fork = &(share->fork[0]);
		else
			philo[i].left_fork = &(share->fork[i + 1]);
	}
	return (philo);
}

int	mutex_init(t_share *data)
{
	int		i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	pthread_mutex_init(&data->mutex_msg, NULL);
	pthread_mutex_init(&data->mutex_last_eat, NULL);
	pthread_mutex_init(&data->mutex_break, NULL);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return (0);
}

int	mutex_destro(t_philo *data)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(&data->share->mutex_msg);
	pthread_mutex_destroy(&data->share->mutex_last_eat);
	pthread_mutex_destroy(&data->share->mutex_break);
	while (i < data->share->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->share->fork[i]);
		i++;
	}
	free(data->share->fork);
	free(data->share);
	free(data);
	return (0);
}

int	get_args(int argc, char **argv, t_share *share)
{
	share->start_t = ft_get_time();
	share->flage = 0;
	share->number_of_philosophers = ft_atoi(argv[1]);
	if (share->number_of_philosophers == 0)
	{
		free(share);
		return (0);
	}
	share->time_to_die = ft_atoi(argv[2]);
	share->time_to_eat = ft_atoi(argv[3]);
	share->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		share->number_of_meals = ft_atoi(argv[5]);
	else
		share->number_of_meals = -1;
	if (share->number_of_meals == 0)
	{
		free(share);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_share	*share;
	t_philo	*philo;

	if (check_args(argc, argv) == 0)
		return (1);
	share = (t_share *)malloc(sizeof(t_share));
	if (!get_args(argc, argv, share))
		return (0);
	mutex_init(share);
	philo = philo_init(share, philo);
	make_philo(philo);
	mutex_destro(philo);
	return (0);
}
