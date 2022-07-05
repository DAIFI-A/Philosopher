#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*p;
	int	stop;

	p = (t_philo *)arg;
	stop = 0;
	while (1)
	{
		if (p->share->number_of_meals != -1 && p->count_meal == p->nbr_meals)
		{
			p->share->flage = 1;
			p->flage = 1;
			return (0);
		}
		if (ft_get_time() - p->last_eat_time >= p->time_to_die)
			exit(1);
		usleep(500);
	}
	return (0);
}