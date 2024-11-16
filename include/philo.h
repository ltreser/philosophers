/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreser <ltreser@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:42:34 by ltreser           #+#    #+#             */
/*   Updated: 2024/11/16 02:02:11 by ltreser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WRONG_INPUT "\033[0;31m Wrong input!\n \033[0;32m Correct input is: \
							./philo 5 800 200 200 [5]\n \033[0m"
# define MALLOC_FAIL "\033[0;31m Malloc failed!\n \033[0m"
# define MUTEX_FAIL "\033[0;31m Failed to init mutex!\n \033[0m"
# define THREAD_FAIL "\033[0;31m Failed to create thread!\n \033[0m"
# define FORK "has taken a fork\n"
# define EATING "is eating\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define DEATH "died\n"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;
typedef enum e_action	t_action;

enum	e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

struct					s_table
{
	long				members;
	long				tt_die;
	long				tt_eat;
	long				tt_sleep;
	long				t_start;
	int					max_meals;
	t_mutex				**forks;
	t_philo				**philos;
	t_mutex				m_write;
	t_mutex				m_meals;
	t_mutex				m_end;
	int					end;
	int					meals;
	pthread_t			monitor_id;
};

struct					s_philo
{
	int					id;
	pthread_t			thread_id;
	long				meals;
	long				t_last_meal;
	t_mutex				*left;
	t_mutex				*right;
	t_table				*table;
	int					max_meals;
	long				tt_eat;
	long				tt_sleep;
	long				tt_die;
	long				t_start;
	long				members;
};

int						reservation_correct(int ac, char **av);
void					make_reservation(t_table *table, int ac, char **av);
long					ft_atol(const char *str);
int						ft_strlen(char *str);
int						isnum_n(char *str, int n);
long					current_ms(void);
void					lay_table(t_table *table);
void					init_forks(t_table *table);
void					init_philos(t_table *table);
void					end_here(t_table *table);
int						check_end(t_table *table);
long					check_meals(t_table *table);
void					be_served(t_philo *philo);
void					*monitor(void *arg);
void					*routine(void *arg);
void					serve_dinner(t_table *table);
long					timestamp(t_philo *philo);
long					check_t_last_meal(t_philo *philo);
void					dinner41(t_philo *philo);
void					free_philos(t_table *table);
void					free_forks(t_table *forks);
void					clear_table(t_table *table);
void					m_write(t_philo *philo, int action);

#endif
