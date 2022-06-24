/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:45:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/06/22 02:16:11 by adaifi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int		passing_args(int ac, char **argv)
{
	t_philo	*data;

	data->share = (t_share *)malloc(sizeof(t_share));
	data->share->number_of_philosophers = ft_atoi(argv[1]);
	if (data->share->number_of_philosophers == 0)
		return (0);
	data->share->time_to_die = ft_atoi(argv[2]);
	data->share->time_to_eat = ft_atoi(argv[3]);
	data->share->time_to_sleep = ft_atoi(argv[4]);
	if (ac == 6)
	{
		data->share->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (data->share->number_of_times_each_philosopher_must_eat == 0)
			return (0);
	}
	return 0;
}

int philo_init(t_philo *philo)
{
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * philo->share->number_of_philosophers);
	if (!philo)
		return(0);
	//write(1, &philo->share->number_of_philosophers, 1);
	while (i < philo->share->number_of_philosophers)
	{
		philo[i].share = philo->share;
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].right_fork = &philo->share->fork[i];
		if (i + 1 == philo->share->number_of_philosophers)
			philo[i].left_fork = &philo->share->fork[0];
		else
			philo[i].left_fork = &philo->share->fork[i + 1];
		i++;
	}
	return 0;
}

int	mutex(t_share *data)
{
	int		i;

	i = 0;
	data->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->mutex)
		return 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return 0;
}

void	*rout(void *data)
{
	t_philo *dat = (t_philo *)data;
	printf("eat");
	return NULL;
}

void	thread_creation(t_philo *data, int res, int i)
{
	data->share->threads = malloc(sizeof(data->share->number_of_philosophers));
	if (data->id % 2 == res)
	{
		pthread_create(&data->share->threads[i], NULL, &rout, data);
	}
}

int make_philo(t_philo *data)
{
	int		i;

	i = 0;
	while (i < data->share->number_of_philosophers)
	{
		puts("oy");
		thread_creation(data, 0, i);
		i++;
	}
	usleep(30);
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
	t_philo *data;
	check_args(argc, argv);
	passing_args(argc, argv);
	philo_init(data);
	make_philo(data);
	return 0;
}
