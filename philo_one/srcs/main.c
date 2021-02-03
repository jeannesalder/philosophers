/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:47:04 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/03 22:02:10 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start_philo(void *arg)
{
	(void)arg;

	return (NULL);
}

int	start_threads(t_arg arg)
{
	int		i;
	pthread_t	id;

	i = 0;
	while (i < arg.nb_philo)
	{
		arg.philo[i] = get_info_philo(arg, i);
		if (pthread_create(&id, NULL, &start_philo, &arg))
			return (handle_error("Error with thread\n"));
		usleep(100);
		i++;
	}
	return (0);
}

int	set_struct(t_arg *arg, char **argv)
{
	(void)arg;
	(void)argv;

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
	if (!arg->nb_philo || !arg->t_die || !arg->t_eat || !arg->t_sleep || !arg->nb_eat)
		return (1);
	return (0);
}

int	main(int ac, char **argv)
{
	t_arg	arg;

	if (ac != 5 && ac != 6)
		return (handle_error_arg("Wrong number of arguments\n"));
	if (set_struct(&arg, argv))
		return (handle_error_arg("Wrong arguments\n"));
	if (xmalloc((void **)&(arg.philo), sizeof(t_philo) * arg.nb_philo))
		return (handle_error("Error with malloc.\n"));
	start_threads(arg);
	free(arg.philo);
}
