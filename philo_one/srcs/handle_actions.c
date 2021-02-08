/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 11:23:08 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/08 16:58:19 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(unsigned long break_time)
{
	unsigned long	end_time;

	end_time = get_time() + break_time;
	while (get_time() < end_time)
		usleep(break_time);
}

int		handle_death(unsigned long start_time, int id, int state)
{
	if (state == 1)
		display_action(start_time, id, "died");
	else
		write(1, "simulation end\n", 15);
	return (state);
}

int		handle_eating(t_philo philo, unsigned long *time_meal)
{
	if (get_time() - *time_meal > (unsigned long)philo.t_die)
		return (handle_death(philo.start_time, philo.id, 1));
	pthread_mutex_lock(philo.waiter);
	pthread_mutex_lock(philo.left_fork);
	display_action(philo.start_time, philo.id, "has taken a fork");
	pthread_mutex_lock(philo.right_fork);
	pthread_mutex_unlock(philo.waiter);
	display_action(philo.start_time, philo.id, "has taken a fork");
	display_action(philo.start_time, philo.id, "is eating");
	ft_usleep(philo.t_eat);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
	*time_meal = get_time();
	if (philo.nb_eat != -1 && philo.nb_meal > philo.nb_eat)
		return (handle_death(philo.start_time, philo.id, 2));
	return (0);
}

int		handle_sleeping(t_philo philo)
{
	display_action(philo.start_time, philo.id, "is sleeping");
	ft_usleep(philo.t_sleep);
	display_action(philo.start_time, philo.id, "is thinking");
	return (0);
}
