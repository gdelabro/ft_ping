/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:34:41 by gdelabro          #+#    #+#             */
/*   Updated: 2020/10/30 18:33:19 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void		stop_ping_loop(int code)
{
	(void)code;
	ping_loop = 0;
}

uint16_t	calc_checksum(t_packet *pckt, int len)
{
	uint32_t sum;

	sum = 0;
	if (len & 1)
	{
		len--;
		sum = *((uint8_t *)pckt + len);
	}
	while (len)
	{
		len -= 2;
		sum += *((unsigned short*)pckt + len / 2);
	}
	while (sum & 0xffff0000)
		sum = (sum & 0xffff) + (sum >> 16);
	return (~((uint16_t)sum));
}

void		creat_packet(t_ping *ping)
{
	int a, b;
	ft_bzero(&ping->pckt, sizeof(ping->pckt));
	ping->pckt.hdr.type = ICMP_ECHO;
	ping->pckt.hdr.un.echo.id = getpid();
	ft_strncpy(ping->pckt.msg, "packet from gdelabro",
			sizeof(ping->pckt.msg) - 1);
	ping->pckt.hdr.un.echo.sequence = ping_loop;
	ping->pckt.hdr.checksum = calc_checksum(&ping->pckt, sizeof(ping->pckt));
}

#include <errno.h>
extern int errno;

int			ping(t_ping *ping)
{
	int send_res;

	setsockopt(ping->sockfd, SOL_IP, IP_TTL, &ping->ttl, sizeof(ping->ttl));
	setsockopt(ping->sockfd, SOL_SOCKET, SO_RCVTIMEO,
			&ping->timeout, sizeof(ping->timeout));
	while (ping_loop)
	{
		creat_packet(ping);
		ping->t1 = get_time_now();
		if (sendto(ping->sockfd, &ping->pckt, sizeof(ping->pckt), 0,
			ping->sock_addr, sizeof(ping->sock_addr)) == -1)
		{
			printf("packet send fail: %d %s\n", errno, strerror(errno));
		}
		//receive packet
		//get time 2
		//write about packet if received correctly
		// wait ???
		ping_loop++;
		ping_loop = 0;
	}
	statistics(ping);
}
