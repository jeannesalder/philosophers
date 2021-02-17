/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:34:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 16:22:01 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	handle_death(t_arg arg)
{
	display_action(arg, "died");
	return (1);
}

void	*monitor_death(void *tmp)
{
	unsigned long	time;
	t_arg			*arg;

	arg = tmp;
	while (1)
	{
		time = get_time();
		if ((int)(time - arg->last_meal) > arg->t_die)
			exit(handle_death(*arg));
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_meal(void *tmp)
{
	int		i;
	t_arg	*arg;

	i = 0;
	arg = tmp;
	while (i < arg->nb_philo)
	{
		sem_wait(arg->end_meal);
		i++;
	}
	end_philo(*arg);
	exit(0);
	return (NULL);
}
