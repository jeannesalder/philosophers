/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:47:04 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 12:34:04 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int		create_philo(t_arg arg, int i)
{
	pid_t		pid;
//	pthread_t	id;

	while (i < arg.nb_philo)
	{
		pid = fork();
		if (pid == -1)
			exit(handle_error("Error with fork", NULL));
		if (pid == 0)
		{
			arg.id = i + 1;
			loop_philo(&arg);
	/*		if (pthread_create(&id, NULL, &monitor, &arg))
				return (handle_error("Error with thread\n", NULL));
			pthread_detach(id);
*/
		}
		i++;
	}
	return (0);
}

int		launch_simu(t_arg arg)
{
	int	i;

	i = 0;
	sem_unlink("forks");
	sem_unlink("end_meal");
	arg.forks = sem_open("forks", O_CREAT, S_IRWXU, arg.nb_philo / 2);
	arg.end_meal = sem_open("end_meal", O_CREAT, S_IRWXU, 0);
	if (!arg.forks || !arg.end_meal)
		return (handle_error("Error with semaphore\n", NULL));
	if (create_philo(arg, 0))
		return (1);
	while (i < arg.nb_philo)
	{
		sem_wait(arg.end_meal);
		i++;
	}
	//end of philo
	return (0);
}

int		set_struct(t_arg *arg, char **argv)
{
	arg->start_time = get_time();
	arg->last_meal = arg->start_time;
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
	if (launch_simu(arg))
		return (1);
}
