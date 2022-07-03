#include "philo.h"

void	right_handed(t_philo *p)
{
	if (!is_dead(p))
		return ;
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%u %d %s\n",  ft_get_time() - p->share->start_t, p->id, "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	if (p->share->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(p->right_fork);
		ft_usleep(p->share->time_to_die);
		return ;
	}
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "is eating");
	pthread_mutex_unlock(&p->share->mutex_msg);
	p->count_meal++;
	pthread_mutex_lock(&p->share->mutex_last_eat);
	p->share->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&p->share->mutex_last_eat);
	ft_usleep(p->share->time_to_eat);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	left_handed(t_philo *p)
{
	if (!is_dead(p))
		return ;
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	if (p->share->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(p->left_fork);
		ft_usleep(p->share->time_to_die);
		return ;
	}
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%u %d %s\n", ft_get_time() - p->share->start_t, p->id, "is eating");
	pthread_mutex_unlock(&p->share->mutex_msg);
	p->count_meal++;
	pthread_mutex_lock(&p->share->mutex_last_eat);
	p->share->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&p->share->mutex_last_eat);
	ft_usleep(p->share->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	eat_task(t_philo *philo)
{
	if (philo->id % 2 == 0)
		right_handed(philo);
	else
		left_handed(philo);
}

void	tasks(t_philo *philo)
{
	if (!is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->share->mutex_break);
	if (!philo->share->flage)
	{
		pthread_mutex_unlock(&philo->share->mutex_break);
		
	}
	pthread_mutex_unlock(&philo->share->mutex_break);
}