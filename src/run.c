/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:23:20 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/16 02:01:28 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner41(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	m_write(philo, TAKE_FORK);
	usleep(philo->tt_die * 1000);
	pthread_mutex_unlock(philo->right);
}

void	be_served(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
	m_write(philo, TAKE_FORK);
	m_write(philo, TAKE_FORK);
	m_write(philo, EAT);
	pthread_mutex_lock(&philo->table->m_meals);
	philo->t_last_meal = current_ms();
	philo->table->meals++;
	pthread_mutex_unlock(&philo->table->m_meals);
	usleep(philo->tt_eat * 1000);
	philo->meals++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	m_write(philo, SLEEP);
	usleep(philo->tt_sleep * 1000);
	m_write(philo, THINK);
}

void	*monitor(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		i = -1;
		while (++i < table->members)
		{
			if ((current_ms()
					- check_t_last_meal(table->philos[i])) > table->tt_die)
			{
				m_write(table->philos[i], DIE);
				pthread_mutex_lock(&table->m_end);
				table->end = 1;
				pthread_mutex_unlock(&table->m_end);
				return (NULL);
			}
		}
		usleep(500);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		plates;
	int		round;
	int		distance;
	int		max_distance;

	philo = (t_philo *)arg;
	if (philo->members == 1 && (!check_end(philo->table))
		&& (!(philo->meals == philo->max_meals)))
		return (dinner41(philo), NULL);
	while ((!check_end(philo->table)) && (!(philo->meals == philo->max_meals)))
	{
		plates = 1;
		if (philo->members > 1)
			plates = philo->members / 2;
		round = (check_meals(philo->table) / plates) + 1;
		distance = (philo->members - (round % philo->members) + philo->id)
			% philo->members;
		max_distance = (plates - 1) * 2;
		if (!(distance % 2) && (distance <= max_distance))
			be_served(philo);
		usleep(500);
	}
	end_here(philo->table);
	return (NULL);
}

void	serve_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_create(&table->monitor_id, NULL, monitor, table))
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
