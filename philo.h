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

#endif
