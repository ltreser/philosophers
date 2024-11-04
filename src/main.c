/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:42:49 by ltreser           #+#    #+#             */
/*   Updated: 2024/10/10 17:31:30 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int ac, char **av)
{
	t_table *table;

	table = malloc(sizeof(table));
	if (reservation_correct(ac, av)) //error handling
	{
		make_reservation(table, ac, av); //parse
		printf("parsing done!\n");
		//lay_table(table); //init
		//serve_dinner(table); //run
		//clear_table(table); //free
	}
	else
		return (printf("%s", WRONG_INPUT), exit(EXIT_FAILURE), 1);
}


