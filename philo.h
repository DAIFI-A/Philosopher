/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:45:29 by adaifi            #+#    #+#             */
/*   Updated: 2022/06/22 02:01:50 by adaifi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<pthread.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>

typedef struct share
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_t		*threads;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*fork;
}		t_share;

typedef struct s_philo
{
	t_share			*share;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	long			last_meal;
}		t_philo;

int		ft_isdigit(int a);
char	*ft_error(char **str);
void	check_args(int ac, char *argv[]);
int		is_digit(char	**av);
void	over_flow(char **av);
int	ft_atoi(const char *str);
void	thread_creation(t_philo *data, int res, int i);
int	mutex(t_share *data);
int philo_init(t_philo *philo);
int		passing_args(int ac, char **argv);
int make_philo(t_philo *data);

#endif