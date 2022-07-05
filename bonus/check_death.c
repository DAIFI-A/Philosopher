#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*p;
	int	stop;

	p = (t_philo *)arg;
	stop = 0;
	while (!stop)
	{
		if (ft_get_time() - p->last_eat_time >= p->time_to_die)
			print_status(p, ft_get_time() - p->share->start_t, "died\n");
        stop = p->flage + p->share->flage;
	}
	return (NULL);
}