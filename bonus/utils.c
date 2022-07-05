/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:43:27 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 22:04:49 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

char	*ft_error(char **str)
{
	write(2, "Error\n", 7);
	exit(1);
}

unsigned int	ft_get_time(void)
{
	unsigned int	ret;
	struct timeval	time;

	ret = 0;
	if (gettimeofday(&time, NULL) == -1)
	{
		perror("gettimeofday() failed");
		return (0);
	}
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	ft_usleep(unsigned int time_in_ms)
{
	unsigned int	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < time_in_ms)
		usleep(100);
}

void	print_status(t_philo *p, unsigned int time, char *status)
{
	int		len;

	pthread_mutex_lock(&p->share->mutex_break);
	if (p->share->flage == 1)
	{
		pthread_mutex_unlock(&p->share->mutex_break);
		return ;
	}
	if (!strcmp(status, "died\n"))
		p->share->flage = 1;
	pthread_mutex_unlock(&p->share->mutex_break);
	printf("%u %u %s", time, p->process_id, status);
}