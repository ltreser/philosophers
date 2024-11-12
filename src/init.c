/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:10:29 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/12 01:48:23 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->members)
	{
		table->forks[i] = malloc(sizeof(t_mutex));
		if (!table->forks[i])
			return (printf("%s", MALLOC_FAIL), end_here(table));
		if (pthread_mutex_init(table->forks[i], NULL))// return 0 indicates success
			return (printf("%s", MUTEX_FAIL), end_here(table));
		i++;
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->members)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		if (!table->philos[i])
			return (printf("%s", MALLOC_FAIL), end_here(table));
		table->philos[i]->meals = 0;
		table->philos[i]->t_last_meal = table->t_start;
		table->philos[i]->id = i + 1;
		table->philos[i]->table = table;
		table->philos[i]->tt_sleep = table->tt_sleep;
		table->philos[i]->max_meals = table->max_meals;
		table->philos[i]->t_start = table->t_start;
		table->philos[i]->members = table->members;
		table->philos[i]->left = table->forks[i];
		table->philos[i]->right = table->forks[(i + 1) % table->members];
		i++;
	}	
}

void	lay_table(t_table *table)
{
	table->forks = malloc(sizeof(t_mutex *) * table->members);
	table->philos = malloc(sizeof(t_philo *) * table->members);
	if (!table->philos || !table->forks)
		return (printf("%s", MALLOC_FAIL), end_here(table));
	table->t_start = current_ms();
	table->end = 0;
	table->meals = 0;
	if (pthread_mutex_init(&table->m_write, NULL))
		return (printf("%s", MUTEX_FAIL), end_here(table));
	if (pthread_mutex_init(&table->m_end, NULL))
		return (printf("%s", MUTEX_FAIL), end_here(table));
	if (pthread_mutex_init(&table->m_meals, NULL))
		return (printf("%s", MUTEX_FAIL), end_here(table));
	init_forks(table);
	init_philos(table);
}
