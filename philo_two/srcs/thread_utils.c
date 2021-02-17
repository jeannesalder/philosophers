/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 11:43:49 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/17 17:54:29 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char			*compose_str(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	int		size;
	char	*dest;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 4;
	if (xmalloc((void **)&dest, size * sizeof(*dest)))
		return (NULL);
	while (s1[j])
		dest[i++] = s1[j++];
	dest[i++] = ' ';
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i++] = ' ';
	j = 0;
	while (s3[j])
		dest[i++] = s3[j++];
	dest[i++] = '\n';
	dest[i] = 0;
	return (dest);
}

void			display_action(t_philo philo, char *action)
{
	char			*str;
	unsigned long	time;

	sem_wait(philo.message);
	time = get_timestamp(philo.start_time);
	str = compose_str(ft_itoa(time), ft_itoa(philo.id), action);
	write(1, str, ft_strlen(str));
	free(str);
	sem_post(philo.message);
}

unsigned long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long	get_timestamp(unsigned long start)
{
	unsigned long	time;

	time = get_time();
	return (time - start);
}
