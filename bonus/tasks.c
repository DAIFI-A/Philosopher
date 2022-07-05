#include "philo_bonus.h"

void	right_handed(t_philo *p, sem_t *mutex)
{
	sem_wait(mutex);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	if (p->n == 1)
	{
		usleep(p->time_to_die * 1000);
		return ;
	}
	sem_wait(mutex);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	print_status(p, ft_get_time() - p->share->start_t, "is eating\n");
	p->count_meal++;
	p->last_eat_time = ft_get_time();
	ft_usleep(p->time_to_eat);
	sem_post(mutex);
	sem_post(mutex);
}

void	left_handed(t_philo *p, sem_t *mutex)
{
	sem_wait(mutex);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	if (p->n == 1)
	{
		usleep(p->time_to_die * 1000);
		return ;
	}
	sem_wait(mutex);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	print_status(p, ft_get_time() - p->share->start_t, "is eating\n");
	p->count_meal++;
	p->last_eat_time = ft_get_time();
	usleep(p->time_to_eat * 1000);
	sem_post(mutex);
	sem_post(mutex);
}

void	eat_task(t_philo *p, sem_t *mutex)
{
	if (p->id % 2 == 0)
		right_handed(p, mutex);
	else
		left_handed(p, mutex);

}

void	tasks(t_philo *p, sem_t *mutex)
{
	eat_task(p, mutex);
	print_status(p, ft_get_time() - p->share->start_t, "is sleeping\n");
	ft_usleep(p->time_to_sleep);
	print_status(p, ft_get_time() - p->share->start_t, "is thinking\n");
	if (p->id % 2 == 0)
		usleep(100);
	return ;
}