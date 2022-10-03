/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:48 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 13:50:46 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	mutex_init(t_program *program)
{
	int	i;

	i = 0;
	program->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					program->num_philo);
	if (program->fork == NULL)
	{
		free(program->philos);
		return (error_message("Malloc error"));
	}
	while (i < program->num_philo)
	{
		if ((pthread_mutex_init(&program->fork[i], NULL) < 0))
			return (error_message("Mutex init error"));
		i++;
	}
	if ((pthread_mutex_init(&program->write, NULL)) < 0)
		return (error_message("Mutex init error"));
	if ((pthread_mutex_init(&program->finish_mutex, NULL)) < 0)
		return (error_message("Mutex init error"));
	return (1);
}

int	philo_init(t_program *program)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * program->num_philo);
	if (philos == NULL)
		return (error_message("Malloc error"));
	while (i < program->num_philo)
	{
		philos[i].id = i + 1;
		philos[i].lfork = i;
		philos[i].rfork = (i + 1) % program->num_philo;
		philos[i].meal_count = 0;
		philos[i].eat_time = get_time();
		philos[i].program = program;
		if (pthread_mutex_init(&philos[i].meal_count_mutex, NULL) < 0)
			return (error_message("Mutex init error"));
		if (pthread_mutex_init(&philos[i].eat_time_mutex, NULL) < 0)
			return (error_message("Mutex init error"));
		i++;
	}
	program->philos = philos;
	return (1);
}

int	input_init(int argc, char **argv, t_program *program)
{
	program->start_time = get_time();
	program->finish = false;
	if (argc < 5 || argc > 6)
		return (error_message("Wrong amount of parameters"));
	if (!ft_atoi_protect(argv[1], &program->num_philo))
		return (error_message("wrong parameter input"));
	if (program->num_philo == 0)
		return (0);
	if (!ft_atoi_protect(argv[2], &program->time_die))
		return (error_message("wrong parameter input"));
	if (!ft_atoi_protect(argv[3], &program->time_eat))
		return (error_message("wrong parameter input"));
	if (!ft_atoi_protect(argv[4], &program->time_sleep))
		return (error_message("wrong parameter input"));
	if (argv[5])
	{
		if (!ft_atoi_protect(argv[5], &program->num_eat))
			return (error_message("wrong parameter input"));
	}
	return (1);
}
