#include "philo.h"

void	check_death(t_philo	*p)
{
	while (1)
	{
		if (ft_get_time() - p->share->last_eat_time > p->share->time_to_die)
		{
			pthread_mutex_lock(&p->share->mutex_break);
            p->share->flage = 1;
			pthread_mutex_unlock(&p->share->mutex_break);
			printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "died");
			return ;
		}
	}
	return ;
}