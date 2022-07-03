#include "philo.h"

void	*check_death(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		
		pthread_mutex_lock(&p->share->mutex_last_eat);
		if (p->share->flage == 1)
		{
			pthread_mutex_unlock(&p->share->mutex_last_eat);
			break ;
		}
		else if (p->share->flage != 1 && ft_get_time() - p->share->last_eat_time > p->share->time_to_die)
		{
			pthread_mutex_unlock(&p->share->mutex_last_eat);
			pthread_mutex_lock(&p->share->mutex_break);
            p->share->flage = 1;
			pthread_mutex_unlock(&p->share->mutex_break);
			pthread_mutex_lock(&p->share->mutex_msg);
			printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "died");
			pthread_mutex_unlock(&p->share->mutex_msg);
            return (NULL);
		}
		pthread_mutex_unlock(&p->share->mutex_last_eat);
	}
	return (NULL);
}

int	is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->share->mutex_break);
	if (p->share->flage == 1)
	{
		pthread_mutex_unlock(&p->share->mutex_break);
		return (0);
	}
	pthread_mutex_unlock(&p->share->mutex_break);
	return (1);
}
