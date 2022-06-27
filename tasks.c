#include "philo.h"

void	right_handed(t_philo *p)
{
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%s", "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	if (p->share->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(p->right_fork);
		ft_usleep(p->share->time_to_die);
		return ;
	}
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%s", "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%s", "is eating");
	pthread_mutex_unlock(&p->share->mutex_msg);
	pthread_mutex_lock(&p->share->mutex_last_eat);
	p->share->last_eat_time = ft_get_time();
	pthread_mutex_unlock(&p->share->mutex_last_eat);
	ft_usleep(p->share->time_to_eat);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	left_handed(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%s\n", "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	if (p->share->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(p->left_fork);
		ft_usleep(p->share->time_to_die);
		return ;
	}
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%s\n", "has taken a fork");
	pthread_mutex_unlock(&p->share->mutex_msg);
	pthread_mutex_lock(&p->share->mutex_msg);
	printf("%s\n", "is eating");
	pthread_mutex_unlock(&p->share->mutex_msg);
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
	eat_task(philo);
	pthread_mutex_lock(&philo->share->mutex_msg);
	printf("%s\n", "is sleeping");
	pthread_mutex_unlock(&philo->share->mutex_msg);
	ft_usleep(philo->share->time_to_sleep);
	pthread_mutex_lock(&philo->share->mutex_msg);
	printf("%s\n", "is thinking");
	pthread_mutex_unlock(&philo->share->mutex_msg);
	if (philo->share->number_of_philosophers % 2 != 0)
		ft_usleep(100);
}