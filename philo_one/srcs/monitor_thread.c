/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:34:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/18 10:40:14 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*handle_death(t_arg *arg, t_philo philo)
{
	(void)arg;
	//display_action(philo, "died");
	pthread_mutex_lock(philo.msg);
	write(1, "YOU DEAD MOTHAFUCKA\n", 20);
	pthread_mutex_unlock(arg->cpy_end);
	return (NULL);
}

void	*handle_end_meal(t_arg *arg)
{
	pthread_mutex_lock(arg->philo[0].msg);
	write(1, "end of simulation\n", 19);
	pthread_mutex_unlock(arg->cpy_end);
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
					return(handle_death(arg, arg->philo[i]));
			if (arg->philo[i].state == 1)
				finished_meal++;
			i++;
			if (finished_meal == arg->nb_philo)
				return (handle_end_meal(arg));
		}
		usleep(1000);
	}
	return (NULL);
}
