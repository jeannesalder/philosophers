/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:28:41 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/03 22:01:30 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	get_time(void)
{
	unsigned long		time;
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	xmalloc(void **ptr, int size)
{
	*ptr = malloc(size);
	if (!*ptr)
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long int	result;

	i = 0;
	result = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((int)result);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
