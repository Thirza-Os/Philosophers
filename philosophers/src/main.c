/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:51 by tosinga           #+#    #+#             */
/*   Updated: 2022/10/03 20:47:58 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char *argv[])
{
	t_program	*program;

	program = (t_program *)malloc(sizeof(t_program));
	if (program == NULL)
		return (error_message("Malloc error"));
	if (input_init(argc, argv, program) && philo_init(program) \
		&& mutex_init(program))
		start_philosophers(program->philos);
	free(program);
	return (0);
}
