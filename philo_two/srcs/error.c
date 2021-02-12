/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:20:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/12 11:09:42 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	handle_error_arg(char *error)
{
	write(2, error, ft_strlen(error));
	printf("Arguments : number_of_philosopher time_to_die\
	time_to_eattime_to_sleep [number_of_time_each_philosophers_must_eat]\n");
	return (1);
}

int	handle_error(char *str, void *item)
{
	if (item)
		free(item);
	write(2, str, ft_strlen(str));
	return (1);
}
