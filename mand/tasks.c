#include "philo.h"

void	right_handed(t_philo *p)
{
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	if (p->n == 1)
	{
		pthread_mutex_unlock(p->right_fork);
		ft_usleep(p->time_to_die);
		return ;
	}
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "is eating\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	p->count_meal++;
	pthread_mutex_lock(&p->share->mutex_last_eat);
	p->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&p->share->mutex_last_eat);
	ft_usleep(p->time_to_eat);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	left_handed(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	if (p->n == 1)
	{
		pthread_mutex_unlock(p->left_fork);
		ft_usleep(p->time_to_die);
		return ;
	}
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "has taken a fork\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "is eating\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	p->count_meal++;
	pthread_mutex_lock(&p->share->mutex_last_eat);
	p->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&p->share->mutex_last_eat);
	ft_usleep(p->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	eat_task(t_philo *p)
{
	if (p->id % 2 == 0)
		right_handed(p);
	else
		left_handed(p);
}

void	tasks(t_philo *p)
{
	eat_task(p);
	if (p->share->number_of_meals != -1 && p->count_meal == p->share->number_of_meals)
	{
		pthread_mutex_lock(&p->share->mutex_break);
		p->flage = 1;
		pthread_mutex_unlock(&p->share->mutex_break);
		//return ;
	}
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "is sleeping\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	ft_usleep(p->time_to_sleep);
	pthread_mutex_lock(&p->share->mutex_msg);
	print_status(p, ft_get_time() - p->share->start_t, "is thinking\n");
	pthread_mutex_unlock(&p->share->mutex_msg);
	if (p->n % 2 != 0)
		ft_usleep(100);
}