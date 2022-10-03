/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:59 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 14:00:54 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// make every other philo wait to prevent deadlock
void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (should_stop(philo) == false)
	{
		if (philo_eat(philo) == false)
			return (NULL);
		if (philo_sleep(philo) == false)
			return (NULL);
		philo_think(philo);
	}
	return (NULL);
}
