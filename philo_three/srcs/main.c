/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:47:04 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 17:13:53 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	end_philo(t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.nb_philo)
	{
		kill(arg.pid[i], SIGTERM);
		i++;
	}
	free(arg.pid);
}

int		create_philo(t_arg arg, int i)
{
	pthread_t	id;

	while (i < arg.nb_philo)
	{
		arg.pid[i] = fork();
		if (arg.pid[i] == -1)
			exit(handle_error("Error with fork", NULL));
		if (arg.pid[i] == 0)
		{
			arg.id = i + 1;
			if (pthread_create(&id, NULL, &monitor_death, &arg))
				return (handle_error("error with thread\n", arg.pid));
			pthread_detach(id);
			loop_philo(&arg);
		}
		i++;
	}
	return (0);
}

int		launch_simu(t_arg arg)
{
	pthread_t	id;

	sem_unlink("forks");
	sem_unlink("end_meal");
	sem_unlink("message");
	arg.forks = sem_open("forks", O_CREAT, S_IRWXU, arg.nb_philo / 2);
	arg.end_meal = sem_open("end_meal", O_CREAT, S_IRWXU, 0);
	arg.message = sem_open("message", O_CREAT, S_IRWXU, 1);
	if (!arg.forks || !arg.end_meal)
		return (handle_error("Error with semaphore\n", arg.pid));
	if (create_philo(arg, 0))
		return (1);
	if (arg.nb_meal != -1)
		if (pthread_create(&id, NULL, &monitor_meal, &arg))
			return (handle_error("error with thread\n", arg.pid));
	waitpid(-1, NULL, 0);
	end_philo(arg);
	return (0);
}

int		set_struct(t_arg *arg, char **argv)
{
	arg->start_time = get_time();
	arg->last_meal = arg->start_time;
	arg->nb_meal = 0;
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
	if (xmalloc((void **)&arg.pid, sizeof(pid_t) * arg.nb_philo))
		return (handle_error("Error with malloc.\n", NULL));
	if (launch_simu(arg))
		return (1);
}
