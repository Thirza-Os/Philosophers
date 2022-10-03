/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:29:43 by tosinga           #+#    #+#             */
/*   Updated: 2022/09/28 13:29:43 by tosinga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi_protect(const char *str, int *dst)
{
	int				i;
	unsigned long	num;

	i = 0;
	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - '0';
		if (num > INT_MAX)
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	*dst = num;
	return (1);
}
