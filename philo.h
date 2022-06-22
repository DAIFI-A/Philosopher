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
	pthread_mutex_t	mutex;
} t_share;


int		ft_isdigit(int a);
char	*ft_error(char **str);
void	check_args(int ac, char *argv[]);
int		is_digit(char	**av);
void	over_flow(char **av);
int	ft_atoi(const char *str);

#endif