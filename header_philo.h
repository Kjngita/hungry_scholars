#ifndef HEADER_PHILOS_H
# define HEADER_PHILOS_H

# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>


typedef struct s_philo
{
	pthread_t	thread_no;
	size_t		id;
	int			alr_ate;
	size_t		ate_enough_times;
	int			alr_slept;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;

}	t_philo;

typedef struct s_mastermind
{

	t_philo	*philo_queue;
}	t_mastermind;

int	ft_atoi(char *str);
int	validate_args(char *arg);
int	print_msg_n_return_value(char *msg, int value);

int	init_philo(int number_of_philos, int ac, char **av);
t_philo	create_philo(int ac, char **av);
void	*start_of_prog(void *arg);

#endif