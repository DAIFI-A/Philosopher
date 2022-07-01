#include "philo.h"

void	*check_death(void *arg)
{
	t_philo	*p;
	int		break_flage;

	p = (t_philo *)arg;
	break_flage = 0;
	while (!break_flage)
	{
		pthread_mutex_lock(&p->share->mutex_last_eat);
		if (ft_get_time() - p->share->last_eat_time >= p->share->time_to_die)
		{
			pthread_mutex_unlock(&p->share->mutex_last_eat);
			pthread_mutex_lock(&p->share->mutex_msg);
			printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "died");
			pthread_mutex_lock(&p->share->mutex_break);
            p->share->flage = 1;
			pthread_mutex_unlock(&p->share->mutex_break);
			pthread_mutex_unlock(&p->share->mutex_msg);
            return (NULL);
		}
		else
			pthread_mutex_unlock(&p->share->mutex_last_eat);
		pthread_mutex_lock(&p->share->mutex_break);
        break_flage = p->flage + p->share->flage;
		pthread_mutex_unlock(&p->share->mutex_break);
	}
	return (NULL);
}