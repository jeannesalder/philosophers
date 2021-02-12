/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:34:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/12 14:38:15 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*handle_death(t_philo philo)
{
	display_action(philo, "died");
	return (NULL);
}

void	*handle_end_meal(void)
{
	write(1, "simulation is over\n", 19);
	return (NULL);
}

void	*monitor(void *tmp)
{
	int				i;
	int				finished_meal;
	unsigned long	time;
	t_arg			*arg;

	arg = tmp;
	while (1)
	{
		i = 0;
		time = get_time();
		finished_meal = 0;
		while (i < arg->nb_philo)
		{
			if ((int)(time - arg->philo[i].last_meal) > arg->t_die)
				return (handle_death(arg->philo[i]));
			if (arg->philo[i].state == 1)
				finished_meal++;
			i++;
			if (finished_meal == arg->nb_philo)
				return (handle_end_meal());
		}
		usleep(1000);
	}
	return (NULL);
}
