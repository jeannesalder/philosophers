/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 17:52:08 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	philo.forks = arg.forks;
	philo.message = arg.message;
	philo.nb_meal = 0;
	philo.state = 0;
	return (philo);
}
