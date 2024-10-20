/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:42:28 by ltreser           #+#    #+#             */
/*   Updated: 2024/10/20 17:24:46 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	n;
	
	n = 0;
	str = 

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	isnum_n(char *str, int n)
{
	int i;

	i = 0;
	if (n == '-1')
		n = ft_strlen(str);
	while (n--)
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

