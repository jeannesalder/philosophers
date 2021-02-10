/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:47:04 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/10 22:44:44 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start_philo(void *tmp)
{
	t_philo *philo;

	philo = tmp;
	while (philo->state != 1)
	{
		handle_eating(philo, *philo);
		handle_sleeping(*philo);
		handle_thinking(*philo);
	}
	return (NULL);
}

void	*monitor(void *tmp)
{
	int	i;
	int	diff;
	int	finished_meal;
	unsigned long time;
	t_arg *arg;

	i = 0;
	finished_meal = 0;
	arg = tmp;
	while (1)
	{
		time = get_time();
		while (i < arg->nb_philo)
		{
			diff = time - arg->philo[i].last_meal;
			if (diff > arg->t_die)
			{
				handle_death(arg->philo[i]);
				pthread_mutex_lock(arg->philo[i].msg);
				pthread_mutex_unlock(arg->cpy_end);
				return (NULL);
			}
			if (arg->philo[i].state == 1)
				finished_meal++;
			i++;
		}
		if (finished_meal == arg->nb_philo)
		{
			pthread_mutex_lock(arg->philo[i].msg);
			write(1, "simulation is over\n", 19);
			pthread_mutex_unlock(arg->cpy_end);
			return (NULL);
		}
		usleep(3000);
		i = 0;
	}
	return (NULL);
}

int		set_threads(t_arg arg)
{
	int			i;
	pthread_t	id;

	i = 0;
	if (pthread_create(&arg.id_thread, NULL, &monitor, &arg))
		return (handle_error("Error with thread\n", arg.philo));
	pthread_detach(arg.id_thread);
	while (i < arg.nb_philo)
	{
		arg.philo[i] = get_info_philo(arg, i);
		if (pthread_create(&id, NULL, &start_philo, &arg.philo[i]))
			return (handle_error("Error with thread\n", arg.philo));
		pthread_detach(id);
		usleep(100);
		i++;
	}
	return (0);
}

int		set_struct(t_arg *arg, char **argv)
{
	arg->time = get_time();
	arg->philo = NULL;
	arg->nb_philo = ft_atoi(argv[1]);
	arg->t_die = ft_atoi(argv[2]);
	arg->t_eat = ft_atoi(argv[3]);
	arg->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		arg->nb_eat = ft_atoi(argv[5]);
	else
		arg->nb_eat = -1;
	if (!arg->nb_philo || !arg->t_die || !arg->t_eat || !arg->t_sleep || \
			!arg->nb_eat)
		return (1);
	return (0);
}

int		main(int ac, char **argv)
{
	t_arg	arg;

	if (ac != 5 && ac != 6)
		return (handle_error_arg("Wrong number of arguments\n"));
	if (set_struct(&arg, argv))
		return (handle_error_arg("Wrong arguments\n"));
	if (xmalloc((void **)&arg.philo, sizeof(t_philo) * arg.nb_philo))
		return (handle_error("Error with malloc.\n", NULL));
	if (set_mutexes(&arg))
		return (handle_error("Error with mutex.\n", arg.philo));
	if (set_threads(arg))
		return (1);
	pthread_mutex_lock(&arg.end);
//	end_philo(&arg);
}
