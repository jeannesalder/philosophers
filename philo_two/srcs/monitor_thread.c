/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:34:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/19 18:10:17 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*handle_death(t_arg arg, t_philo philo)
{
	char			*str;
	unsigned long	time;

	sem_wait(arg.message);
	time = get_timestamp(philo.start_time);
	str = compose_str(ft_itoa(time), ft_itoa(philo.id), "died");
	write(1, str, ft_strlen(str));
	free(str);
	sem_post(arg.ending);
	return (NULL);
}

void	*handle_end_meal(t_arg arg)
{
	sem_wait(arg.message);
	write(1, "end of simulation\n", 18);
	sem_post(arg.ending);
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
				return (handle_death(*arg, arg->philo[i]));
			if (arg->philo[i].state == 1)
				finished_meal++;
			i++;
			if (finished_meal == arg->nb_philo)
				return (handle_end_meal(*arg));
		}
		usleep(1000);
	}
	return (NULL);
}
