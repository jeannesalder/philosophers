/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:34:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 18:16:52 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int		handle_death(t_arg *arg)
{
	char			*str;
	unsigned long	time;

	sem_wait(arg->message);
	time = get_timestamp(arg->start_time);
	str = compose_str(ft_itoa(time), ft_itoa(arg->id), "died");
	write(1, str, ft_strlen(str));
	free(str);
	return (1);
}

void	*monitor_death(void *tmp)
{
	unsigned long	time;
	t_arg			*arg;

	arg = tmp;
	while (1)
	{
		time = get_time();
		if ((int)(time - arg->last_meal) > arg->t_die)
			exit(handle_death(arg));
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_meal(void *tmp)
{
	int		i;
	t_arg	*arg;

	i = 0;
	arg = tmp;
	while (i < arg->nb_philo)
	{
		sem_wait(arg->end_meal);
		i++;
	}
	sem_wait(arg->message);
	write(1, "end of simulation\n", 18);
	end_philo(*arg);
	exit(0);
	return (NULL);
}
