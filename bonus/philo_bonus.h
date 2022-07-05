/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:45:29 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 17:59:54 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include<string.h>

typedef struct s_share
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				flage;
	unsigned int	start_t;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_break;
	pthread_mutex_t	*fork;
}		t_share;

typedef struct s_philo
{
	t_share			*share;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				n;
	int				id;
	int				process_id;
	int				process;
	int				nbr_meals;
	int				flage;
	int				count_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned int	last_eat_time;
	pthread_t		death;
}		t_philo;

void			over_flow(char **av);
void			check_args(int ac, char *argv[]);
void			ft_usleep(unsigned int time_in_ms);
void			tasks(t_philo *p, sem_t *mutex);
void			right_handed(t_philo *p, sem_t *mutex);
void			left_handed(t_philo *p, sem_t *mutex);
void			eat_task(t_philo *p, sem_t *mutex);
void			*check_death(void *arg);
void			print_status(t_philo *p, unsigned int time, char *status);
void			routine(t_philo *philo, sem_t *mutex);
void			create_thread(t_philo *philo, sem_t *mutex);
void			check_stat(t_philo *philo, t_share *share);
char			*ft_error(char **str);
int				thread_init(t_philo *p);
int				ft_isdigit(int a);
int				is_digit(char **av);
int				ft_atoi(const char *str);
int 			passing_args(int ac, char **argv);
unsigned int	ft_get_time(void);
t_philo 		*philo_init(t_share *share);

#endif