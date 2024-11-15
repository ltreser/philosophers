/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 01:32:07 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/15 21:33:58 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->members && table->philos[i])
	{
		free(table->philos[i]);
		table->philos[i] = NULL;
	}
	i = -1;
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

void	free_forks(t_table *table)
{
	int i;

	i = -1;
	
	while (++i < table->members && table->forks[i])
	{
		pthread_mutex_destroy(table->forks[i]);
		free(table->forks[i]);
		table->forks[i] = NULL;
	}
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
}	

void	clear_table(t_table *table)
{
	if (table)
	{
		free_philos(table);
		free_forks(table);
		pthread_mutex_destroy(&table->m_write);
		pthread_mutex_destroy(&table->m_end);
		pthread_mutex_destroy(&table->m_meals);
		free(table);
		table = NULL;
	}
}
		
