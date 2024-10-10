/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:42:49 by ltreser           #+#    #+#             */
/*   Updated: 2024/10/10 16:08:44 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




int	main(int ac, char **av)
{
	(void)av;
	if (5 == ac || 6 == ac)
		printf("asdf\n");
	else
		return (printf("%s", WRONG_INPUT), exit(EXIT_FAILURE), 1);
}


