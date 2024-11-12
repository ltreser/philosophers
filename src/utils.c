/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:42:28 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/12 01:24:37 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	n;
	int 	i;
	
	n = 0;
	i = 0;
	while (str[i])
	{
		n = (str[i] + '0') * 10;
		i++;
	}
	return (n);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


//takes a string and checks if its only numbers for n length, length -1 = check everything
int	isnum_n(char *str, int n)
{
	int i; 	

	i = 0;
	if (n == -1)
		n = ft_strlen(str);
	while (n--)
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

long current_ms(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long current_ms;
	current_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (current_ms);
}

long timestamp(t_philo *philo)
{
	long	time_passed;

	time_passed = current_ms() - philo->t_start;
	return (time_passed);
}















