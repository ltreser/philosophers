#include "philo.h"

int	reservation_correct(int ac, char **av)
{
	int i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	if (ac == 6 && !isnum_n(av[5] + 1, ft_strlen(av[5] - 2)))
		return (0);
	if (ac == 6 && !(av[5][0] == '[' && av[5][ft_strlen(av[5]) - 1] == ']'))
		return (0);
	while (++i < 5)
		if (!isnum_n(av[i], -1) || ft_atol(av[i]) > INT_MAX || (i > 1 && ft_atol(av[i]) < 60))
			return (0);
	return (1);
}

void	make_reservation(t_table *table, int ac, char **av)
{
	if (ac == 6)
		table->max_meals = (int)ft_atol(av[5] + 1);
	else
		table->max_meals = -1;
	table->members = (int)ft_atol(av[1]);
	table->tt_die = (int)ft_atol(av[2]);
	table->tt_eat = (int)ft_atol(av[3]);
	table->tt_sleep = (int)ft_atol(av[4]);
}
