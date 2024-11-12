/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:23:20 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/12 02:17:27 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	be_served(t_philo *philo)
{
	// XXX when writing always make sure no one died yet
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&philo->table->m_write);
	if (!check_end(philo->table))
		printf("%ld %d %s", timestamp(philo), philo->id, FORK);
	if (!check_end(philo->table))
		printf("%ld %d %s", timestamp(philo), philo->id, FORK);
	if (!check_end(philo->table))
		printf("%ld %d %s", timestamp(philo), philo->id, EAT);
	pthread_mutex_unlock(&philo->table->m_write);
	usleep(philo->tt_eat * 1000);
	philo->meals++;
	pthread_mutex_lock(&philo->table->m_meals);
	philo->t_last_meal = current_ms();
	philo->table->meals++;
	pthread_mutex_unlock(&philo->table->m_meals);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_lock(&philo->table->m_write);
	if (!check_end(philo->table))
		printf("%ld %d %s", timestamp(philo), philo->id, SLEEP);
	pthread_mutex_unlock(&philo->table->m_write);
	usleep(philo->tt_sleep * 1000);
	pthread_mutex_lock(&philo->table->m_write);
	if (!check_end(philo->table))
		printf("%ld %d %s", timestamp(philo), philo->id, THINK);
	pthread_mutex_unlock(&philo->table->m_write);
}

void	*monitor(void *arg)
{
	int i;

	t_table *table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->members)
		{
			if ((current_ms() - check_t_last_meal(table->philos[i])) > table->tt_die)
			// TODO time last meal always changed with meal locked
			{
				pthread_mutex_lock(&table->m_end);
				pthread_mutex_lock(&table->m_write);
				if (!check_end(table))
					printf("%ld %d %s", timestamp(table->philos[i]), i + 1, DEATH);
				table->end = 1;
				pthread_mutex_unlock(&table->m_write);
				pthread_mutex_unlock(&table->m_end);
				return (NULL);
			}
			i++;
		}
	}
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int plates;
	int round;
	int served;
	while (!check_end(philo->table) && !(philo->meals == philo->max_meals))
	{
		plates = philo->members / 2;
		round = check_meals(philo->table) / plates;
		served = check_meals(philo->table) % plates;
		if (!served && round == philo->id)
			be_served(philo);
		else if (served && ((round + served * 2) == philo->id))
			be_served(philo);
	}
	return (NULL);
}

void serve_dinner(t_table *table)
{
	int i;
	
	i = 0;
	printf("table members: %ld\n", table->members);
	exit(0);
	if (pthread_create(&table->monitor_id, NULL, monitor, table)) // return 0 indicates success
		return (printf("%s", THREAD_FAIL), end_here(table));
	while (i < table->members)		
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL, routine,
				table->philos[i]))
			return (printf("%s", THREAD_FAIL), end_here(table));
		i++;
	}
	i = -1;
	pthread_join(table->monitor_id, NULL);
	while (++i < table->members)
		pthread_join(table->philos[i]->thread_id, NULL);
	
}
