/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:52:30 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/03 22:02:22 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct	s_philo
{
	int		id;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	unsigned long	last_meal;
	int		state;
	int		start;
}			t_philo;

typedef struct	s_arg
{
	unsigned long	time;
	int		nb_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_eat;
	t_philo		*philo;
}		t_arg;

/*
 ** main.c
*/

/*
 ** error.c
*/
int	handle_error_arg(char *error);
int	handle_error(char *str);

/*
 ** thread_utils.c
*/
t_philo	get_info_philo(t_arg arg, int i);

/*
 ** utils.c
*/

unsigned long	get_time(void);
int	xmalloc(void **ptr, int size);
int	ft_atoi(char *str);
int	ft_strlen(char *str);

#endif
