#include "philo.h"

void	init_forks(t_table *table)
{
	int i;

	i = 0;
	while (i < table->members)
	{
		table->forks[i] = i + 1;
		if (pthread_mutex_init()
	//TODO init pointer array properly so i dont have to use points just arrows

void	lay_table(t_table *table)
{
	table->forks = malloc(sizeof(t_fork) * table->members);
	table->philos = malloc(sizeof(t_philo) * table->members);
	if (!table->philos || !table->forks)
		return (printf("%s", MALLOC_FAIL), exit(EXIT_FAILURE));
	table->t_start = current_ms();
	init_forks(table);
}
