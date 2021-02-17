/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:52:30 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 12:30:02 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_arg
{
	unsigned long	start_time;
	unsigned long	last_meal;
	int				id;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	int				nb_meal;
	sem_t			*forks;
	sem_t			*end_meal;
}					t_arg;

/*
 ** monitor_thread.c
*/

void				*monitor(void *tmp);

/*
 ** error.c
*/
int					handle_error_arg(char *error);
int					handle_error(char *str, void *item);

/*
 ** libft_utils.c
*/

int					xmalloc(void **ptr, int size);
int					ft_atoi(char *str);
int					ft_strlen(char *str);

/*
 ** process_utils.c
*/
void				display_action(t_arg arg, char *action);
unsigned long		get_time(void);
unsigned long		get_timestamp(unsigned long start_time);

/*
 ** ft_itoa.c
*/

char				*ft_itoa(unsigned long nbr);

/*
 ** philo_process.c
*/
void				ft_usleep(unsigned long break_time);
void				handle_eating(t_arg *arg);
void				loop_philo(t_arg *arg);

/*
 ** end_simulation.c
*/
void				end_philo(t_arg *arg);
int					is_finish(t_arg arg);

#endif
