/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:23:20 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/11 00:11:18 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_table *table = (t_table *)arg;
	//TODO: infinity loop that continuously checks if the philos have died
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int	plates;
	int round;
	int	served;

	plates = philo->table->members / 2;
	round = meals / plates;
	served = meals % plates;
	if (!served && round == philo->thread_id)
		//eat blablabla
	else if (served && ((round + served * 2) == philo->thread_id))
		//eat blablabla
}

void	serve_dinner(t_table *table)
{
	int i;

	i = 0;
	if (pthread_create(&table->monitor_id, NULL, monitor, table)) // return 0 indicates success
		return (printf("%s", THREAD_FAIL), exit(EXIT_FAILURE));
	while (i < table->members)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL, routine, table->philos[i]))
			return (printf("%s", THREAD_FAIL), exit(EXIT_FAILURE));
		i++;
	}
}



/*	t_philo *philo = (t_philo *)arg;
	(void)philo;
	(void)arg;
	return NULL;
}*/
