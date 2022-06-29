#include "philo.h"

void	*check_death(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&p->share->mutex_last_eat);
		if (ft_get_time() - p->share->last_eat_time >= p->share->time_to_die)
		{
			pthread_mutex_unlock(&p->share->mutex_last_eat);
			pthread_mutex_lock(&p->share->mutex_msg);
			printf("%lu %d %s\n", ft_get_time() - p->share->start_t, p->id,"died");
			pthread_mutex_unlock(&p->share->mutex_msg);
            p->flage = 1;
            return (NULL);
		}
		else
			pthread_mutex_unlock(&p->share->mutex_last_eat);
	}
	return (NULL);
}