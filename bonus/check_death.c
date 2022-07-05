#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*p;
	int	stop;

	p = (t_philo *)arg;
	stop = 0;
	while (1)
	{
		if (ft_get_time() - p->last_eat_time >= p->time_to_die)
			exit(0);
		usleep(100);
	}
	return (0);
}