/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:10:29 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/10 22:11:17 by ltreser          ###   ########.fr       */
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
			return (printf("%s", MALLOC_FAIL), exit(EXIT_FAILURE));
		if (pthread_mutex_init(table->forks[i], NULL))// return 0 indicates success
			return (printf("%s", MUTEX_FAIL), exit(EXIT_FAILURE));
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
		table->philos[i]->meals = 0;
		table->philos[i]->t_last_meal = table->t_start;
		table->philos[i]->id = i + 1;
		table->philos[i]->left = table->forks[i];
		table->philos[i]->right = table->forks[(i + 1) % table->members];
		if (pthread_create(&table->philos[i]->thread_id, NULL, serve_dinner,
				table->philos[i])) // return 0 indicates success
			return (printf("%s", THREAD_FAIL), exit(EXIT_FAILURE));
		i++;
	}	
}

void	lay_table(t_table *table)
{
	table->forks = malloc(sizeof(t_mutex *) * table->members);
	table->philos = malloc(sizeof(t_philo *) * table->members);
	if (!table->philos || !table->forks)
		return (printf("%s", MALLOC_FAIL), exit(EXIT_FAILURE));
	table->t_start = current_ms();
	if (pthread_mutex_init(&table->write, NULL))
		return (printf("%s", MUTEX_FAIL), exit(EXIT_FAILURE));
	if (pthread_mutex_init(&table->round, NULL))
		return (printf("%s", MUTEX_FAIL), exit(EXIT_FAILURE));
	if (pthread_mutex_init(&table->death, NULL))
		return (printf("%s", MUTEX_FAIL), exit(EXIT_FAILURE));
	init_forks(table);
	init_philos(table);
}
