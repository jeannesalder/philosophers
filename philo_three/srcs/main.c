/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:47:04 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/16 18:30:48 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	end_philo(t_arg *arg)
{
	free(arg->philo);
	free(arg->forks);
	sem_close(arg->forks);
	sem_unlink("forks");
}

int		create_philo(t_arg arg, int i)
{

	while (i < arg.nb_philo)
	{
		arg.philo[i] = get_info_philo(arg, i);
		if (pthread_create(&id, NULL, &start_philo, &arg.philo[i]))
			return (handle_error("Error with thread\n", arg.philo));
		pthread_detach(id);
		usleep(50);
		i++;
	}
	return (0);
}

int		set_threads(t_arg arg)
{
	pthread_t	id;

	sem_unlink("forks");
	arg.forks = sem_open("forks", O_CREAT, S_IRWXU, arg.nb_philo / 2);
	if (!arg.forks || !arg.ending)
		return (handle_error("Error with semaphore\n", arg.philo));
	if (create_philo(arg, 0))
		return (1);
	if (pthread_create(&id, NULL, &monitor, &arg))
		return (handle_error("Error with thread\n", arg.philo));
	pthread_detach(id);
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
	if (set_threads(arg))
		return (1);
	end_philo(&arg);
}
