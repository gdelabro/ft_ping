/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:02:00 by gdelabro          #+#    #+#             */
/*   Updated: 2020/10/23 22:08:38 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

size_t	get_time_now(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	return (current_time.tv_sec * 1000000 + current_time.tv_usec);
}

int		diff_time(size_t t1, size_t t2)
{
	return (t2 - t1);
}
