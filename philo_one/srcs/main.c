/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:47:04 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/08 16:57:25 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start_philo(void *tmp)
{
	t_philo *philo;

	philo = tmp;
	while (philo->state == 0)
	{
		philo->state = handle_eating(*philo, &(philo->last_meal));
		philo->nb_meal++;
		handle_sleeping(*philo);
	}
	return (NULL);
}

int		set_threads(t_arg arg)
{
	int			i;
	pthread_t	id;

	i = 0;
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

void	end_philo(t_arg *arg)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&arg->waiter);
	while (i < arg->nb_philo)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		i++;
	}
	free(arg->philo);
	free(arg->forks);
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
	int i = 0;
	while (1)
		i = 1;
	end_philo(&arg);
}
