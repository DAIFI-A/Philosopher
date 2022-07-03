/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:45:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/03 02:43:03 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
# include<pthread.h>

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
		philo[i].flage = 0;
		philo[i].count_meal = 0;
		philo[i].nbr_meals = share->number_of_meals;
		philo[i].right_fork = &(share->fork[i]);
		if (i + 1 == share->number_of_philosophers)
			philo[i].left_fork = &(share->fork[0]);
		else
			philo[i].left_fork = &(share->fork[i + 1]);
		i++;
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
	return 0;
}

void	*rout(void *data)
{
	t_philo *dat;

	dat = (t_philo *)data;
	dat->share->last_eat_time = dat->share->start_t;
	// if (pthread_create(&dat->death, NULL, &check_death, dat) != 0)
	// 	perror("failed to create thread");
	while(!(dat->share->flage))
	{
		tasks(dat);
		// printf("%d\n", dat->share->flage);
		// pthread_mutex_lock(&dat->share->mutex_break);
		// if (dat->share->flage == 1 || dat->flage == 1)
		// {
		// 	pthread_mutex_unlock(&dat->share->mutex_break);
		// 	break ;
		// }
		// pthread_mutex_unlock(&dat->share->mutex_break);
		// break_flage = dat->share->flage + dat->flage;
	}
	// pthread_join(dat->death, NULL);
	return (NULL);
}

int make_philo(t_philo *data)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->share->number_of_philosophers);
	while (i < data->share->number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, &rout, &data[i]);
		i++;
	}
	// i = 0;
	// while (i < data->share->number_of_philosophers)
	// {
	// 	pthread_join(threads[i], NULL);
	// 	i++;
	// }
	return (0);
}

int main(int argc, char *argv[])
{
	t_share	*share;
	t_philo	*philo;

	share = (t_share *)malloc(sizeof(t_share));
	check_args(argc, argv);
	share->start_t = ft_get_time();
	share->flage = 0;
	share->number_of_philosophers = ft_atoi(argv[1]);
	if (share->number_of_philosophers == 0)
		return (0);
	share->time_to_die = ft_atoi(argv[2]);
	share->time_to_eat = ft_atoi(argv[3]);
	share->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		share->number_of_meals = ft_atoi(argv[5]);
		if (share->number_of_meals == 0)
			return (0);
	}
	else 
		share->number_of_meals = -1;
	mutex_init(share);
	philo = philo_init(share);
	make_philo(philo);
	check_death(philo);
	// pthread_mutex_destroy(&share->mutex_msg);
	// pthread_mutex_destroy(&share->mutex_last_eat);
	// pthread_mutex_destroy(&share->mutex_break);
	// free(share);
	// free(philo);
	return 0;
}
