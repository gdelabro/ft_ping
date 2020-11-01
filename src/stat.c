/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:42:30 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/01 19:36:54 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void	calc_stat(void)
{
	size_t t;

	t = diff_time(ping_s.t1, ping_s.t2);
	if (t <= ping_s.min)
		ping_s.min = t;
	if (t >= ping_s.max)
		ping_s.max = t;
	ping_s.avg += t;
}

void	statistics(void)
{
	if (!ping_s.sent)
		exit(0);
	printf("--- %s ping statistics ---\n", ping_s.host);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %zums\n"
			, ping_s.sent, ping_s.received,
			100 - ping_s.received * 100 / ping_s.sent,
			(get_time_now() - ping_s.start) / 1000);
	ping_s.received ? printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
				(float)ping_s.min / 1000,
				(float)ping_s.avg / (ping_s.received * 1000),
				(float)ping_s.max / 1000,
				(float)ping_s.mdev / 1000) : 0;
	exit(0);
}
