/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:43:38 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 22:44:08 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *arg)
{
	t_philo	*p;
	int		stop;

	p = (t_philo *)arg;
	stop = 0;
	while (!stop)
	{
		pthread_mutex_unlock(&p->share->mutex_break);
		pthread_mutex_lock(&p->share->mutex_last_eat);
		if (ft_get_time() - p->last_eat_time >= p->time_to_die)
		{
			pthread_mutex_unlock(&p->share->mutex_last_eat);
			pthread_mutex_lock(&p->share->mutex_msg);
			print_status(p, ft_get_time() - p->share->start_t, "died\n");
			pthread_mutex_unlock(&p->share->mutex_msg);
		}
		else
			pthread_mutex_unlock(&p->share->mutex_last_eat);
		pthread_mutex_lock(&p->share->mutex_break);
		stop = p->flage + p->share->flage;
	}
	pthread_mutex_unlock(&p->share->mutex_break);
	return (NULL);
}
