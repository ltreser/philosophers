/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:42:34 by ltreser           #+#    #+#             */
/*   Updated: 2024/10/20 16:42:36 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

#define RESET "\033[0m"           // Resets all styles
#define BLACK "\033[0;30m"        // Black text
#define RED "\033[0;31m"          // Red text
#define GREEN "\033[0;32m"        // Green text
#define YELLOW "\033[0;33m"       // Yellow text
#define BLUE "\033[0;34m"         // Blue text
#define MAGENTA "\033[0;35m"      // Magenta text
#define CYAN "\033[0;36m"         // Cyan text
#define WHITE "\033[0;37m"        // White text

#define WRONG_INPUT RED "Wrong input!\n" GREEN "Correct input is: ./philo 5 800 200 200 [5]\n" RESET
#define MALLOC_FAIL RED "Malloc failed!\n" RESET

typedef struct s_table t_table;
typedef struct s_philo t_philo;
typedef struct s_fork t_fork;
typedef pthread_mutex_t t_mutex;

struct	s_table
{
	long	members;
	long	tt_die;
	long	tt_eat;
	long 	tt_sleep;
	long	t_start;
	int	max_meals; //-1 if no input
	t_fork	**forks;
	t_philo	**philos;

};

struct s_fork
{
        int     id;
        t_mutex fork;
};

struct s_philo
{
	int		id;
	pthread_t	thread_id;
	long		meals;
	long		t_last_meal;
	t_fork		*left;
	t_fork		*right;
};


int     reservation_correct(int ac, char **av);
void    make_reservation(t_table *table, int ac, char **av);
long    ft_atol(const char *str);
int     ft_strlen(char *str);
int     isnum_n(char *str, int n);
long	current_ms(void);

#endif
