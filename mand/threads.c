/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:34:43 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 22:40:19 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*rout(void *data)
{
	t_philo	*dat;
	int		break_flage;

	dat = (t_philo *)data;
	dat->last_eat_time = dat->share->start_t;
	pthread_create(&dat->death, NULL, &check_death, dat);
	break_flage = 0;
	while (!break_flage)
	{
		tasks(dat);
		pthread_mutex_lock(&dat->share->mutex_break);
		break_flage = dat->share->flage + dat->flage;
		pthread_mutex_unlock(&dat->share->mutex_break);
	}
	pthread_join(dat->death, NULL);
	return (NULL);
}

int	make_philo(t_philo *data)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * \
	data->share->number_of_philosophers);
	while (i < data->share->number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, &rout, &data[i]);
		i++;
	}
	i = 0;
	while (i < data->share->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}
