/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <jgonfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:20:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2021/02/03 18:10:47 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int     handle_error_arg(char *error)
{
        write(2, error, ft_strlen(error));
        //ajouter manuel d'utilisation ici.
        return (1);
}

int	handle_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
