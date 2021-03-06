/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:45:29 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 22:42:27 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<pthread.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<sys/time.h>
# include<string.h>

typedef struct share
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
	int				nbr_meals;
	int				flage;
	int				count_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned int	last_eat_time;
	pthread_t		death;
}		t_philo;

int				over_flow(char **av);
int				check_args(int ac, char *argv[]);
void			ft_usleep(unsigned int time_in_ms);
void			tasks(t_philo *philo);
void			right_handed(t_philo *p);
void			left_handed(t_philo *p);
void			eat_task(t_philo *philo);
void			*check_death(void *arg);
void			*rout(void *data);
void			print_status(t_philo *p, unsigned int time, char *status);
int				ft_error(char **str);
int				ft_isdigit(int a);
int				is_digit(char **av);
int				ft_atoi(const char *str);
int				mutex_fork_init(t_share *data);
int				passing_args(int ac, char **argv);
int				get_args(int argc, char **argv, t_share *share);
int				make_philo(t_philo *data);
int				mutex_destro(t_philo *data);
int				mutex_init(t_share *data);
unsigned int	ft_get_time(void);
t_philo			*philo_init(t_share	*share, t_philo *philo);

#endif