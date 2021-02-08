/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/08 16:18:37 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int		set_mutexes(t_arg *arg)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&arg->waiter, NULL))
		return (1);
	if (xmalloc((void **)&arg->forks, sizeof(pthread_mutex_t) * arg->nb_philo))
		return (1);
	while (i < arg->nb_philo)
	{
		if (pthread_mutex_init(&arg->forks[i], NULL))
		{
			free(arg->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

t_philo	get_info_philo(t_arg arg, int i)
{
	t_philo philo;

	philo.id = i + 1;
	philo.t_die = arg.t_die;
	philo.t_eat = arg.t_eat;
	philo.t_sleep = arg.t_sleep;
	philo.last_meal = arg.time;
	philo.start_time = arg.time;
	philo.nb_eat = arg.nb_eat;
	philo.nb_meal = 0;
	philo.state = 0;
	philo.waiter = &arg.waiter;
	philo.left_fork = &arg.forks[i];
	if (philo.id == arg.nb_philo)
		philo.right_fork = &arg.forks[0];
	else
		philo.right_fork = &arg.forks[philo.id];
	return (philo);
}
