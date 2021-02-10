/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 11:23:08 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/10 15:38:14 by jgonfroy         ###   ########.fr       */
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

int		handle_death(t_philo philo)
{
	display_action(philo, "died");
	pthread_mutex_lock(philo.msg);
	return (1);
}

t_philo	handle_eating(t_philo *ptr, t_philo philo)
{
	pthread_mutex_lock(philo.waiter);
	pthread_mutex_lock(philo.left_fork);
	display_action(philo, "has taken a fork");
	pthread_mutex_lock(philo.right_fork);
	pthread_mutex_unlock(philo.waiter);
	display_action(philo, "has taken a fork");
	display_action(philo, "is eating");
	ft_usleep(philo.t_eat);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
	ptr->last_meal = get_time();
	ptr->nb_meal++;
	if (philo.nb_eat != -1 && ptr->nb_meal >= philo.nb_eat)
		ptr->state = 1;
	return (philo);
}

void	handle_sleeping(t_philo philo)
{
	display_action(philo, "is sleeping");
	ft_usleep(philo.t_sleep);
}

void	handle_thinking(t_philo philo)
{
	display_action(philo, "is thinking");
}
