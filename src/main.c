/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:42:49 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/10 23:36:38 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int ac, char **av)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("%s", MALLOC_FAIL), exit(EXIT_FAILURE), 1);
	if (reservation_correct(ac, av)) //error handling
	{
		make_reservation(table, ac, av); //parse
		printf("parsing done!\n");
		lay_table(table); //init
		printf("init done!\n");
		serve_dinner(table); //run
		//clear_table(table); //free
	}
	else
		return (printf("%s", WRONG_INPUT), exit(EXIT_FAILURE), 1);
}

