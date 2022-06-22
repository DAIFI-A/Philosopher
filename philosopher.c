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
	t_share	*share;

	share = (t_share *)malloc(sizeof(t_share *));
	share->number_of_philosophers = ft_atoi(argv[1]);
	if (share->number_of_philosophers == 0)
		return (0);
	share->time_to_die = ft_atoi(argv[2]);
	share->time_to_eat = ft_atoi(argv[3]);
	share->time_to_sleep = ft_atoi(argv[4]);
	if (ac == 6)
	{
		share->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (share->number_of_times_each_philosopher_must_eat == 0)
			return (0);
	}
	return 0;
}

void	*rout(void *data)
{
	t_share *philo = (t_share *)malloc(sizeof(t_share *));
	philo = (t_share *)data;
	pthread_mutex_lock(&philo->mutex);
	printf("eat");
	pthread_mutex_unlock(&philo->mutex);
	return NULL;
}

void	thread_creation(t_share *data)
{
	int		i;

	i = 0;
	pthread_mutex_init(&data->mutex, NULL);
	data->threads = malloc(sizeof(data->number_of_philosophers));
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->threads[i], NULL, &rout, (void *)data);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
}

int main(int argc, char *argv[])
{
	t_share *share;
	check_args(argc, argv);
	passing_args(argc, argv);
	thread_creation(share);
	return 0;
}
