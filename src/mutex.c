/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:06:49 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/16 02:01:49 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_here(t_table *table)
{
	pthread_mutex_lock(&table->m_end);
	table->end = 1;
	pthread_mutex_unlock(&table->m_end);
}

int	check_end(t_table *table)
{
	int	e;

	e = 0;
	pthread_mutex_lock(&table->m_end);
	e = table->end;
	pthread_mutex_unlock(&table->m_end);
	return (e);
}

long	check_meals(t_table *table)
{
	long	m;

	m = 0;
	pthread_mutex_lock(&table->m_meals);
	m = table->meals;
	pthread_mutex_unlock(&table->m_meals);
	return (m);
}

long	check_t_last_meal(t_philo *philo)
{
	long	t;

	t = 0;
	pthread_mutex_lock(&philo->table->m_meals);
	t = philo->t_last_meal;
	pthread_mutex_unlock(&philo->table->m_meals);
	return (t);
}

void	m_write(t_philo *philo, int action)
{
	if (!check_end(philo->table))
	{
		pthread_mutex_lock(&philo->table->m_write);
		if (action == 0)
			printf("%ld %d %s", timestamp(philo), philo->id, FORK);
		if (action == 1)
			printf("%ld %d %s", timestamp(philo), philo->id, EATING);
		if (action == 2)
			printf("%ld %d %s", timestamp(philo), philo->id, SLEEPING);
		if (action == 3)
			printf("%ld %d %s", timestamp(philo), philo->id, THINKING);
		if (action == 4)
			printf("%ld %d %s", timestamp(philo), philo->id, DEATH);
		pthread_mutex_unlock(&philo->table->m_write);
	}
}
