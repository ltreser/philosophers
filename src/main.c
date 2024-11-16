/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:42:49 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/16 01:27:59 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("%s", MALLOC_FAIL), end_here(table), 1);
	if (reservation_correct(ac, av))
	{
		make_reservation(table, ac, av);
		lay_table(table);
		serve_dinner(table);
		clear_table(table);
	}
	else
		return (free(table), table = NULL, printf("%s", WRONG_INPUT),
			exit(EXIT_FAILURE), 1);
}
