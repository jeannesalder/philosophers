/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:22 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/03 18:36:17 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	get_info_philo(t_arg arg, int i)
{
	t_philo philo;

	philo.id = i;
	philo.t_die = arg.t_die;
	philo.t_sleep = arg.t_sleep;
	philo.last_meal = arg.time;
	return (philo);
}
