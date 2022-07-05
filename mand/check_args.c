/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:44:49 by adaifi            #+#    #+#             */
/*   Updated: 2022/07/05 22:43:14 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	over_flow(char **av)
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
				return (ft_error(av));
		}
		i++;
	}
	return (1);
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
			if (ft_isdigit(av[i][j]) == 0 || ft_atoi(av[i]) > 2147483647 \
			|| ft_atoi(av[i]) < 0)
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
		return (ft_error(argv));
	if (over_flow(argv) == 0)
		return (0);
	if (!is_digit(argv))
		return (ft_error(argv));
	return (1);
}
