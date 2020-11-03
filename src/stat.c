/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:42:30 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/03 16:58:57 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void	calc_stat(void)
{
	size_t t;
	size_t mdev;

	t = diff_time(g_ping.t1, g_ping.t2);
	if (t <= g_ping.min)
		g_ping.min = t;
	if (t >= g_ping.max)
		g_ping.max = t;
	g_ping.avg += t;
	mdev = g_ping.avg / g_ping.received;
	mdev = (t > mdev ? t - mdev : mdev - t);
	mdev += g_ping.mdev * (g_ping.received - 1);
	g_ping.mdev = mdev / g_ping.received;
}

void	statistics(void)
{
	if (!g_ping.sent)
		exit(0);
	printf("--- %s ping statistics ---\n", g_ping.host);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %zums\n"
			, g_ping.sent, g_ping.received,
			100 - g_ping.received * 100 / g_ping.sent,
			(get_time_now() - g_ping.start) / 1000);
	g_ping.received ? printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
				(float)g_ping.min / 1000,
				(float)g_ping.avg / (g_ping.received * 1000),
				(float)g_ping.max / 1000,
				(float)g_ping.mdev / 1000) : 0;
	exit(0);
}
