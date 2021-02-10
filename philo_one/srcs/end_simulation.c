/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:42:46 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/10 16:39:50 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    end_philo(t_arg *arg)
{
    int i;

    i = 0;
	pthread_mutex_unlock(&arg->waiter);
	pthread_mutex_destroy(&arg->waiter);
    pthread_mutex_unlock(arg->cpy_end);
	pthread_mutex_destroy(arg->cpy_end);
	while (i < arg->nb_philo)
    {
        pthread_mutex_destroy(&arg->forks[i]);
        i++;
    }
    free(arg->philo);
    free(arg->forks);
}
