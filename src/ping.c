/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:34:41 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/02 18:20:20 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void		end_of_ping(int code)
{
	(void)code;
	ping_s.ping_loop = 0;
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

void		creat_packet()
{
	int a, b;
	ft_bzero(&ping_s.pckt, sizeof(ping_s.pckt));
	ping_s.pckt.hdr.type = ICMP_ECHO;
	ping_s.pckt.hdr.un.echo.id = getpid();
	ft_strncpy(ping_s.pckt.msg, "packet from gdelabro",
			sizeof(ping_s.pckt.msg) - 1);
	ping_s.pckt.hdr.un.echo.sequence = ping_s.ping_loop;
	ping_s.pckt.hdr.checksum = calc_checksum(&ping_s.pckt, sizeof(ping_s.pckt));
}

int			ping(void)
{
	setsockopt(ping_s.sockfd, SOL_IP, IP_TTL, &ping_s.ttl, sizeof(ping_s.ttl));
	setsockopt(ping_s.sockfd, SOL_SOCKET, SO_RCVTIMEO,
			&ping_s.timeout, sizeof(ping_s.timeout));
	ping_s.start = get_time_now();
	while (ping_s.ping_loop < ping_s.c || !ping_s.c)
	{
		ping_s.ping_loop++;
		creat_packet(ping);
		ping_s.t1 = get_time_now();
		if (sendto(ping_s.sockfd, &ping_s.pckt, sizeof(ping_s.pckt), 0,
			ping_s.sock_addr, sizeof(*ping_s.sock_addr)) == -1)
		{
			ping_s.v ? printf("Failed to send packet\n") : 0;
			continue ;
		}
		ping_s.sent++;
		ft_bzero(&ping_s.msg, sizeof(ping_s.msg));
		if (recvmsg(ping_s.sockfd, &ping_s.msg, 0) == -1)
		{
			ping_s.v ? printf("Timeout exceeded on packet %d\n", ping_s.ping_loop) : 0;
			continue ;
		}
		ping_s.t2 = get_time_now();
		ping_s.received++;
		calc_stat();
		printf("64 bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3f ms\n",
			ping_s.host, ping_s.ip, ping_s.ping_loop, ping_s.ttl,
				(float)diff_time(ping_s.t1, ping_s.t2) / 1000);
		usleep(1000000 * (int)(ping_s.i * 1000) / 1000);
	}
	end_of_ping(0);
}
