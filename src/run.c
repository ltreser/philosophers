/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:23:20 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/13 22:59:53 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	be_served(t_philo *philo)
{
	//printf("\n\n\nSOMEONE IS SERVED (philo nr %d)!\n", philo->id);
	// XXX when writing always make sure no one died yet
	if (philo->id == 1)
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->left);
	}
	else
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
	}
	//printf("1 hi im %d and im being served at %ld\n", philo->id, timestamp(philo));
	//printf("time last meal for nr %d is now: %ld\n", philo->id, philo->t_last_meal);
	pthread_mutex_lock(&philo->table->m_write);
	if (!check_end(philo->table))
	{
		printf("%ld %d %s", timestamp(philo), philo->id, FORK);
		printf("%ld %d %s", timestamp(philo), philo->id, FORK);
		printf("%ld %d %s", timestamp(philo), philo->id, EAT);
	}
	pthread_mutex_unlock(&philo->table->m_write);
	pthread_mutex_lock(&philo->table->m_meals);
	philo->t_last_meal = current_ms();
	philo->table->meals++;
	pthread_mutex_unlock(&philo->table->m_meals);
	usleep(philo->tt_eat * 1000);
	philo->meals++;
	if (philo->id == 1)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
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
	int debug;

	t_table *table = (t_table *)arg;
	debug = 0;
	while (1)
	{
		i = 0;
		while (i < table->members)
		{
			//write(1, "1 goes here!\n", 13);
			//debug = current_ms() - check_t_last_meal(table->philos[i]);
			//printf("1 time since last meal: %d\ntime to die: %ld\n", debug, table->tt_die);
			if ((current_ms() - check_t_last_meal(table->philos[i])) > table->tt_die)
			// TODO time last meal always changed with meal locked
			{
				debug = current_ms() - check_t_last_meal(table->philos[i]);
				printf("time no %d since last meal: %d\n", table->philos[i]->id, debug);
				//printf("previous meal timestamp: %ld\n", table->philos[i]->t_last_meal);
				//write(1, "2 goes here!\n", 13);
				pthread_mutex_lock(&table->m_write);
				if (!check_end(table))
					printf("%ld %d %s", timestamp(table->philos[i]), i + 1, DEATH);
				pthread_mutex_unlock(&table->m_write);
				pthread_mutex_lock(&table->m_end);
				table->end = 1;
				pthread_mutex_unlock(&table->m_end);
				return (NULL);
			}
			usleep(500);
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
	while ((!check_end(philo->table)) && (!(philo->meals == philo->max_meals)))
	{
		//printf("\nHI im %d\n", philo->id);
		plates = philo->members / 2;
		//printf("check meals result: %ld\n", check_meals(philo->table));
		round = (check_meals(philo->table) / plates) + 1;
		served = check_meals(philo->table) % plates;
		//printf("this is plates: %d\nthis is round: %d\nthis is plates served: %d\n", plates, round, served);
		if (!served && (round % philo->members == philo->id))
		{
			//printf("I GET FOOD\n");
			//printf("\n\n1 hi im %d and im being served at %ld\n", philo->id, timestamp(philo));
			be_served(philo);
		}
		else if (served && (((round + (served * 2)) % philo->members) == philo->id))
		{
			//printf("I GET FOOD\n");
			//printf("\n\n2 hi im %d and im being served at %ld\n", philo->id, timestamp(philo));
			be_served(philo);
		}
		else if (served && philo->id == philo->members && (!((round + (served * 2)) % philo->members)))
			be_served(philo);
		else if (!served && philo->id == philo->members && (!(round % philo->members)))
			be_served(philo);
		usleep(500);
	}
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
