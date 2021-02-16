/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:17:11 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/07 19:45:49 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static size_t	get_size(unsigned long n)
{
	unsigned int count;

	count = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void		recursion(long int n, char *s, unsigned int i)
{
	if (n < 10)
		s[i] = n + '0';
	else
	{
		recursion(n / 10, s, i - 1);
		s[i] = n % 10 + '0';
	}
}

char			*ft_itoa(unsigned long nbr)
{
	char		*s;
	size_t		size;

	size = get_size(nbr);
	if (!(s = malloc((size + 1) * sizeof(char))))
		return (NULL);
	recursion(nbr, s, size - 1);
	s[size] = 0;
	return (s);
}
