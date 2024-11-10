/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:23:20 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/11 00:58:39 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	be_served(t_philo *philo)
{
	

void	*monitor(void *arg)
{
	int i;

	i = 0;
	t_table *table = (t_table *)arg;
	while (1)
	{
		while (i < table->members)
		{
			pthread_mutex_lock(&table->meals);
			if ((current_ms() - table->philos[i]->t_last_meal) > table_>tt_die) //TODO time last meal always changed with meal locked
			{
				pthread_mutex_lock(&table->death);
				table->death = 1;
				pthread_mutex_unlock(&table->death);
				pthread_mutex_unlock(&table->meals);
				return ;
			}
			pthread_mutex_unlock(&table->meals);
			i++;
		}
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int	plates;
	int round;
	int	served;
	pthread_mutex_lock(&philo->table->death);
	pthread_mutex_lock(&philo->table->meals);
	while (!philo->table->death && !(philo->meals == philo->max_meals))
	{
		pthread_mutex_unlock(&philo->table->meals);
		pthread_mutex_unlock(&philo->table->death);
		plates = philo->members / 2;
		round = meals / plates;
		served = meals % plates;
		if (!served && round == philo->id) //TODO correct
			be_served(philo);
		else if (served && ((round + served * 2) == philo->id)) //TODO it could be that a higher id reaches this first so it should still work -> this is a race condition bc the philos access this randomly and not in order
			be_served(philo);
	pthread_mutex_lock(&philo->table->death);
	pthread_mutex_lock(&philo->table->meals);
	}
	pthread_mutex_unlock(&philo->table->meals);
	pthread_mutex_unlock(&philo->table->death);
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
