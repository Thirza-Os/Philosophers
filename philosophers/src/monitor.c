/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:54 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 14:05:18 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	philo_died(t_program *program, t_philo	*philo)
{
	int				i;
	unsigned long	wait_time;

	i = 0;
	while (i < program->num_philo)
	{
		pthread_mutex_lock(&philo[i].eat_time_mutex);
		wait_time = get_time() - philo[i].eat_time;
		pthread_mutex_unlock(&philo[i].eat_time_mutex);
		if (wait_time > (unsigned long)program->time_die)
		{
			print_info(philo, DIE);
			pthread_mutex_lock(&program->finish_mutex);
			program->finish = true;
			pthread_mutex_unlock(&program->finish_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	philo_full(t_program *program, t_philo *philo)
{
	int	i;
	int	meal_count;

	i = 0;
	while (i < program->num_philo)
	{
		pthread_mutex_lock(&philo[i].meal_count_mutex);
		meal_count = philo[i].meal_count;
		pthread_mutex_unlock(&philo[i].meal_count_mutex);
		if (meal_count < program->num_eat)
			return (false);
		i++;
	}
	pthread_mutex_lock(&program->finish_mutex);
	program->finish = true;
	pthread_mutex_unlock(&program->finish_mutex);
	return (true);
}

void	monitor(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	while (1)
	{
		if (philo_died(program, philo))
			return ;
		if (program->num_eat > 0 && philo_full(program, philo) == true)
			return ;
	}
}
