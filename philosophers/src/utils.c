/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:30:02 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 16:38:19 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//miliseconds
unsigned long	get_time(void)
{
	unsigned long	ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

//microseconds
unsigned long	get_time_usleep(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

bool	ft_usleep_finish_check(unsigned long sleep_time, t_philo *philo)
{
	unsigned long	start;
	t_program		*program;

	sleep_time = sleep_time * 1000;
	program = (t_program *)philo->program;
	start = get_time_usleep();
	while (get_time_usleep() - start < sleep_time)
	{
		pthread_mutex_lock(&program->finish_mutex);
		if (program->finish == true)
		{
			pthread_mutex_unlock(&program->finish_mutex);
			return (false);
		}
		pthread_mutex_unlock(&program->finish_mutex);
		usleep(100);
	}
	return (true);
}

void	ft_usleep(unsigned long sleep_time)
{
	unsigned long	start;

	sleep_time = sleep_time * 1000;
	start = get_time_usleep();
	while (get_time_usleep() - start < sleep_time)
	{
		usleep (100);
	}
}

void	print_info(t_philo *philo, int action)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->program->write);
	time = get_time() - philo->program->start_time;
	pthread_mutex_lock(&philo->program->finish_mutex);
	if (action == TAKE_FORK && philo->program->finish == false)
		printf("%zu %i has taken a fork\n", time, philo->id);
	if (action == EATING && philo->program->finish == false)
		printf("%zu %i is eating\n", time, philo->id);
	if (action == SLEEPING && philo->program->finish == false)
		printf("%zu %i is sleeping\n", time, philo->id);
	if (action == THINKING && philo->program->finish == false)
		printf("%zu %i is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->program->finish_mutex);
	if (action == DIE)
		printf("%zu %i died\n", time, philo->id);
	pthread_mutex_unlock(&philo->program->write);
}
