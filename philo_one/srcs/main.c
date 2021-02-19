/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:47:04 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/19 11:17:46 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	end_philo(t_arg arg)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&arg.msg);
	pthread_mutex_destroy(&arg.end);
	while (i < arg.nb_philo)
		pthread_mutex_destroy(&arg.forks[i++]);
	free(arg.philo);
	free(arg.forks);
}

int		create_philo(t_arg arg, int i)
{
	pthread_t	id;

	while (i < arg.nb_philo)
	{
		arg.philo[i] = get_info_philo(arg, i);
		if (pthread_create(&id, NULL, &start_philo, &arg.philo[i]))
			return (handle_error("Error with thread\n", arg.philo));
		pthread_detach(id);
		usleep(50);
		i = i + 2;
	}
	return (0);
}

int		set_threads(t_arg arg)
{
	if (create_philo(arg, 0))
		return (1);
	usleep(50);
	if (create_philo(arg, 1))
		return (1);
	if (pthread_create(&arg.id_thread, NULL, &monitor, &arg))
		return (handle_error("Error with thread\n", arg.philo));
	pthread_detach(arg.id_thread);
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
	usleep(arg.t_die * 1000);
	end_philo(arg);
}
