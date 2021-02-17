/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 11:23:08 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 12:32:34 by jgonfroy         ###   ########.fr       */
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

void	handle_eating(t_arg *arg)
{
	sem_wait(arg->forks);
	display_action(*arg, "has taken a fork");
	display_action(*arg, "has taken a fork");
	display_action(*arg, "is eating");
	arg->last_meal = get_time();
	ft_usleep(arg->t_eat);
	sem_post(arg->forks);
	arg->nb_meal++;
	if (arg->nb_eat != -1 && arg->nb_meal == arg->nb_eat)
		sem_post(arg->end_meal);
}

void	loop_philo(t_arg *arg)
{
	while (1)
	{
		handle_eating(arg);
		display_action(*arg, "is sleeping");
		ft_usleep(arg->t_sleep);
		display_action(*arg, "is thinking");
	}
}
