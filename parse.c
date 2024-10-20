#include "philo.h"

int	reservation_correct(int ac, char **av)
{
	int i;

	i = 0;
	if (ac < 5 && ac > 6)
		return (0);
	if (ac == 6 && !isnum_m(av[5] + 1, ft_strlen(av[5] - 2)))
		return (0);
	if (ac == 6 && !(av[5][0] == '[' && av[5][ft_strlen(av[5] - 1)] == ']'))
		return (0);
	while (++i < 5)
		if (!isnum_n(av[i], -1))
			return (0);
	
	
		
	//input actually numbers -> only positive
	//no bigger than max int
	//timestamps > 60ms
	//
	//
	//
	//TODO write isnum_n ft that can check n chars for being numeric
	//TODO write atol
	//
}
