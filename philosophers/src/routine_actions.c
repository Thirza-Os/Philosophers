/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:31:41 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 16:37:58 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// alternate to prevent from deadlock
void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->fork[philo->lfork]);
	print_info(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->program->fork[philo->rfork]);
	print_info(philo, TAKE_FORK);
}

bool	philo_eat(t_philo *philo)
{
	pick_up_forks(philo);
	pthread_mutex_lock(&philo->eat_time_mutex);
	philo->eat_time = get_time();
	pthread_mutex_unlock(&philo->eat_time_mutex);
	if (philo->program->num_eat > 0)
	{
		pthread_mutex_lock(&philo->meal_count_mutex);
		philo->meal_count += 1;
		pthread_mutex_unlock(&philo->meal_count_mutex);
	}
	print_info(philo, EATING);
	if (ft_usleep_finish_check(philo->program->time_eat, philo) == false)
	{
		pthread_mutex_unlock(&philo->program->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->program->fork[philo->rfork]);
		return (false);
	}
	pthread_mutex_unlock(&philo->program->fork[philo->lfork]);
	pthread_mutex_unlock(&philo->program->fork[philo->rfork]);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	print_info(philo, SLEEPING);
	if (ft_usleep_finish_check(philo->program->time_sleep, philo) == false)
		return (false);
	return (true);
}

void	philo_think(t_philo *philo)
{
	print_info(philo, THINKING);
}

bool	should_stop(t_philo *philo)
{
	t_program	*program;
	bool		finish;

	program = philo->program;
	pthread_mutex_lock(&program->finish_mutex);
	finish = program->finish;
	pthread_mutex_unlock(&program->finish_mutex);
	return (finish);
}
