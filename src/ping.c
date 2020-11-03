/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:34:41 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/03 17:01:30 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void		end_of_ping(int code)
{
	(void)code;
	g_ping.ping_loop = 0;
	statistics();
	exit(0);
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

void		creat_packet(void)
{
	int a;
	int b;

	ft_bzero(&g_ping.pckt, sizeof(g_ping.pckt));
	g_ping.pckt.hdr.type = ICMP_ECHO;
	g_ping.pckt.hdr.un.echo.id = getpid();
	ft_strncpy(g_ping.pckt.msg, "packet from gdelabro",
			sizeof(g_ping.pckt.msg) - 1);
	g_ping.pckt.hdr.un.echo.sequence = g_ping.ping_loop;
	g_ping.pckt.hdr.checksum = calc_checksum(&g_ping.pckt, sizeof(g_ping.pckt));
}

void		g_pingend_receive(void)
{
	g_ping.ping_loop++;
	creat_packet();
	g_ping.t1 = get_time_now();
	if (sendto(g_ping.sockfd, &g_ping.pckt, sizeof(g_ping.pckt), 0,
				g_ping.sock_addr, sizeof(*g_ping.sock_addr)) == -1)
	{
		g_ping.v ? printf("Failed to send packet\n") : 0;
		return ;
	}
	g_ping.sent++;
	ft_bzero(&g_ping.msg, sizeof(g_ping.msg));
	if (recvmsg(g_ping.sockfd, &g_ping.msg, 0) == -1)
	{
		if (g_ping.v)
			printf("Timeout exceeded on packet %d\n", g_ping.ping_loop);
		return ;
	}
	g_ping.t2 = get_time_now();
	g_ping.received++;
	calc_stat();
	!g_ping.q ? printf("64 bytes from %s (%s): \
icmp_seq=%d ttl=%d time=%.3f ms\n",
			g_ping.host, g_ping.ip, g_ping.ping_loop, g_ping.ttl,
			(float)diff_time(g_ping.t1, g_ping.t2) / 1000) : 0;
	usleep(1000000 * (int)(g_ping.i * 1000) / 1000);
}

int			ping(void)
{
	setsockopt(g_ping.sockfd, SOL_IP, IP_TTL, &g_ping.ttl, sizeof(g_ping.ttl));
	setsockopt(g_ping.sockfd, SOL_SOCKET, SO_RCVTIMEO,
			&g_ping.timeout, sizeof(g_ping.timeout));
	g_ping.start = get_time_now();
	while (g_ping.ping_loop < g_ping.c || !g_ping.c)
		g_pingend_receive();
	end_of_ping(0);
}
