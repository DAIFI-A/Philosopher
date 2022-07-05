/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:44:49 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 22:04:56 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

void	over_flow(char **av)
{
	int		i;
	int		j;
	int		n;

	i = 1;
	while (av[i])
	{
		j = 0;
		n = 0;
		while (av[i][j] != '\0')
		{
			while (av[i][j] == '0' || av[i][j] == '-' || av[i][j] == '+')
				j++;
			while (av[i][j])
			{
				j++;
				n++;
			}
			if (n > 10)
				ft_error(av);
		}
		i++;
	}
}

int	is_digit(char	**av)
{
	int		j;
	int		i;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0 || ft_atoi(av[i]) > 2147483647 || ft_atoi(av[i]) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(int ac, char **argv)
{
	char	*str;
	int		i;

	if (ac < 5 || ac > 6)
		ft_error(argv);
	over_flow(argv);
	if (!is_digit(argv))
		ft_error(argv);
}
