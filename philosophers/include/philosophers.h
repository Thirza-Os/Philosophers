/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:28 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 13:50:13 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef enum e_action
{
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIE,
	OVER,
}	t_action;

typedef struct s_philo
{
	int					id;
	int					lfork;
	int					rfork;

	pthread_mutex_t		meal_count_mutex;
	int					meal_count;

	pthread_mutex_t		eat_time_mutex;
	unsigned long		eat_time;

	struct s_program	*program;
	pthread_t			id_thread;
}	t_philo;

typedef struct s_program
{
	int				counter;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	unsigned long	start_time;

	bool			finish;
	pthread_mutex_t	finish_mutex;

	pthread_t		monitor_thread;	

	pthread_mutex_t	*fork;
	pthread_mutex_t	write;

	t_philo			*philos;

}	t_program;

int				ft_atoi_protect(const char *str, int *dst);
int				error_message(char *str);
int				ft_isdigit(int c);
int				validate(int s);
int				input_init(int argc, char *argv[], t_program *program);
int				philo_init(t_program *program);
int				mutex_init(t_program *program);
void			start_philosophers(t_philo *philos);
void			monitor(t_philo *philo);
void			print_info(t_philo *philo, int action);
unsigned long	get_time(void);
void			ft_usleep(unsigned long sleep_time);
bool			ft_usleep_finish_check(unsigned long sleep_time, \
				t_philo *philo);
void			*routine(void *arg);
void			pick_up_forks(t_philo *philo);
bool			philo_eat(t_philo *philo);
bool			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
bool			should_stop(t_philo *philo);

#endif
