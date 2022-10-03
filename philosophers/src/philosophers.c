/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:57 by tosinga           #+#    #+#             */
/*   Updated: 2022/10/03 17:41:11 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	destroy_mutexes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->program->num_philo)
	{
		pthread_mutex_destroy(&philos->program->fork[i]);
		pthread_mutex_destroy(&philos[i].meal_count_mutex);
		pthread_mutex_destroy(&philos[i].eat_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&philos->program->write);
	pthread_mutex_destroy(&philos->program->finish_mutex);
	free(philos->program->fork);
}

// Make calling thread wait for the philo threads to terminate
static void	join_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->program->num_philo)
	{
		if (pthread_join((philos + i)->id_thread, NULL) != 0)
		{
			error_message("Failed to join thread");
			return ;
		}
		i++;
	}
	return ;
}

static int	make_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->program->num_philo)
	{
		if (pthread_create(&(philos + i)->id_thread, NULL, &routine, \
			philos + i) != 0)
		{
			error_message("Failed to create thread");
			return (0);
		}
		i++;
	}
	return (1);
}

static void	*one_philo(t_philo *philo)
{
	print_info(philo, TAKE_FORK);
	ft_usleep(philo->program->time_die);
	print_info(philo, DIE);
	return (NULL);
}

void	start_philosophers(t_philo *philos)
{
	int		i;

	i = 0;
	if (philos->program->num_philo == 1)
	{
		one_philo(philos);
		free(philos);
		return ;
	}
	if (!make_threads(philos))
	{
		free(philos);
		return ;
	}
	monitor(philos);
	join_threads(philos);
	destroy_mutexes(philos);
	free(philos);
}
