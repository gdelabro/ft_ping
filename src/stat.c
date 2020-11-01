/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:42:30 by gdelabro          #+#    #+#             */
/*   Updated: 2020/10/26 18:53:54 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void	statistics(t_ping *ping)
{
	if (!ping->sent)
		exit(0);
	printf("--- %s ping statistics ---\n", ping->host);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %zums\n"
			, ping->sent, ping->received, ping->received * 100 / ping->sent,
			ping->time);
	exit(0);
}
