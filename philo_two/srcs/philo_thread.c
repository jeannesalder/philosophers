/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 11:23:08 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 17:00:58 by jgonfroy         ###   ########.fr       */
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

void	handle_eating(t_philo *philo)
{
	sem_wait(philo->forks);
	display_action(*philo, "has taken a fork");
	display_action(*philo, "has taken a fork");
	display_action(*philo, "is eating");
	philo->last_meal = get_time();
	ft_usleep(philo->t_eat);
	sem_post(philo->forks);
	philo->nb_meal++;
	if (philo->nb_eat != -1 && philo->nb_meal >= philo->nb_eat)
		philo->state = 1;
}

void	*loop_philo(void *tmp)
{
	t_philo *philo;

	philo = tmp;
	while (1)
	{
		handle_eating(philo);
		display_action(*philo, "is sleeping");
		ft_usleep(philo->t_sleep);
		display_action(*philo, "is thinking");
	}
	return (NULL);
}
