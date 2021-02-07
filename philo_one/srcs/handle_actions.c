/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 11:23:08 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/07 22:48:45 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	handle_eating(t_philo philo)
{
	//verif si le temps et toujours bon;

	pthread_mutex_lock(philo.waiter);
	pthread_mutex_lock(philo.left_fork);
	display_action(philo.start_time, philo.id, "has taken a fork");
	pthread_mutex_lock(philo.right_fork);
	pthread_mutex_unlock(philo.waiter);
	display_action(philo.start_time, philo.id, "has taken a fork");
	display_action(philo.start_time, philo.id, "is eating");
	usleep(philo.t_eat * 1000);
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
	gettimeofday(&philo.last_meal, NULL);
	philo.nb_meal++;
	//verif si le nombre de repas n'est pas depasse
	return (0);
}
