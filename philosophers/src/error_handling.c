/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:45 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 13:29:46 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_message(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, "Error: ", 7);
	write(2, str, i);
	write(2, "\n", 1);
	return (0);
}
