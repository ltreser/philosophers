/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:23:20 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/15 21:56:54 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner41(t_philo *philo)
{
		
		pthread_mutex_lock(philo->right);
		printf("%ld %d %s", timestamp(philo), philo->id, FORK);
		usleep(philo->tt_die * 1000);
}

void	be_served(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
	m_write(philo, 0);
	m_write(philo, 0);
	m_write(philo, 1);
	pthread_mutex_lock(&philo->table->m_meals);
	philo->t_last_meal = current_ms();
	philo->table->meals++;
	pthread_mutex_unlock(&philo->table->m_meals);
	usleep(philo->tt_eat * 1000);
	philo->meals++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	m_write(philo, 2);
	usleep(philo->tt_sleep * 1000);
	m_write(philo, 3);
}

void	*monitor(void *arg)
{
	int i;
	int debug;

	t_table *table = (t_table *)arg;
	debug = 0;
	while (1)
	{
		i = 0;
		while (i < table->members)
		{
			if ((current_ms() - check_t_last_meal(table->philos[i])) > table->tt_die)
			{
				debug = current_ms() - check_t_last_meal(table->philos[i]);
				pthread_mutex_lock(&table->m_write);
				if (!check_end(table))
					printf("%ld %d %s", timestamp(table->philos[i]), i + 1, DEATH);
				pthread_mutex_unlock(&table->m_write);
				pthread_mutex_lock(&table->m_end);
				table->end = 1;
				pthread_mutex_unlock(&table->m_end);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int plates;
	int round;
	int served;
	if (philo->members == 1)
		return (dinner41(philo), NULL);
	while ((!check_end(philo->table)) && (!(philo->meals == philo->max_meals)))
	{
		plates = 1;
		if (philo->members > 1)
			plates = philo->members / 2;
		round = (check_meals(philo->table) / plates) + 1;
		served = check_meals(philo->table) % plates;
		if (!served && (round % philo->members == philo->id))
			be_served(philo);
		else if (served && (((round + (served * 2)) % philo->members) == philo->id))
			be_served(philo);
		else if (served && philo->id == philo->members && (!((round + (served * 2)) % philo->members)))
			be_served(philo);
		else if (!served && philo->id == philo->members && (!(round % philo->members)))
			be_served(philo);
		usleep(500);
	}
	end_here(philo->table);
	return (NULL);
}

void serve_dinner(t_table *table)
{
	int i;
	
	i = 0;
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
