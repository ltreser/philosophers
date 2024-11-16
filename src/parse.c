/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:16:40 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/16 17:31:11 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	reservation_correct(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	while (++i < ac)
		if (!isnum_n(av[i], -1) || ft_atol(av[i]) > INT_MAX || (i > 1
				&& i < 5 && ft_atol(av[i]) < 60))
			return (0);
	if (av[1][0] == '0')
		return (0);
	return (1);
}

void	make_reservation(t_table *table, int ac, char **av)
{
	if (ac == 6)
		table->max_meals = (int)ft_atol(av[5]);
	else
		table->max_meals = -1;
	table->members = (int)ft_atol(av[1]);
	table->tt_die = (int)ft_atol(av[2]);
	table->tt_eat = (int)ft_atol(av[3]);
	table->tt_sleep = (int)ft_atol(av[4]);
}
