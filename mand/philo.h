/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mck-d <mck-d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:45:29 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/01 19:19:52 by mck-d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<pthread.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<sys/time.h>

typedef struct share
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				flage;
	unsigned int	start_t;
	unsigned int	last_eat_time;
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
	int				id;
	long			last_meal;
	int				nbr_meals;
	int				flage;
	int				count_meal;
	pthread_t		death;
}		t_philo;

void			over_flow(char **av);
void			check_args(int ac, char *argv[]);
void			ft_usleep(unsigned int time_in_ms);
void			tasks(t_philo *philo);
void			right_handed(t_philo *p);
void			left_handed(t_philo *p);
void			eat_task(t_philo *philo);
void			*check_death(void *arg);
void			*rout(void *data);
char			*ft_error(char **str);
int				ft_isdigit(int a);
int				is_digit(char **av);
int				ft_atoi(const char *str);
int				mutex_fork_init(t_share *data);
int 			passing_args(int ac, char **argv);
int 			make_philo(t_philo *data);
unsigned int	ft_get_time(void);
t_philo 		*philo_init(t_share *share);

#endif