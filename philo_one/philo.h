/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:52:30 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/10 16:32:13 by jgonfroy         ###   ########.fr       */
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
	int		state;
	int		start;
	int		nb_eat;
	int		nb_meal;
	unsigned long	last_meal;
	unsigned long	start_time;
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*msg;
}			t_philo;

typedef struct	s_arg
{
	unsigned long	time;
	int		nb_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_eat;
	pthread_t		id_thread;
	pthread_mutex_t	waiter;
	pthread_mutex_t	msg;
	pthread_mutex_t	end;
	pthread_mutex_t	*cpy_end;
	pthread_mutex_t	*forks;
	t_philo		*philo;
}		t_arg;

/*
 ** main.c
*/

/*
 ** error.c
*/
int	handle_error_arg(char *error);
int	handle_error(char *str, void *item);

/*
 ** set_threads.c
*/
int	set_mutexes(t_arg *arg);
t_philo	get_info_philo(t_arg arg, int i);

/*
 ** libft_utils.c
*/

unsigned long	get_time(void);
unsigned long	get_timestamp(unsigned long start_time);

int	xmalloc(void **ptr, int size);
int	ft_atoi(char *str);
int	ft_strlen(char *str);

/*
 ** libft_utils.c
*/
void	display_action(t_philo philo, char *action);

/*
 ** ft_itoa.c
*/

char	*ft_itoa(unsigned long nbr);

/*
 ** handle_actions.c
*/
void	ft_usleep(unsigned long break_time);
int		handle_death(t_philo philo);
t_philo	handle_eating(t_philo *ptr, t_philo philo);
void	handle_sleeping(t_philo philo);
void	handle_thinking(t_philo philo);

/*
 ** end_simulation.c
*/
void	end_philo(t_arg *arg);
int		is_finish(t_arg arg);

#endif
