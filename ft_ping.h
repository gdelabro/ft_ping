/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 20:47:40 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/01 19:17:13 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "ft_printf/ft_printf.h"
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <time.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>

# include <errno.h>

# define DEFAULT_TTL 64
# define DEFAULT_TIMEOUT 1
# define PACKET_SIZE 64

//int					ping_loop;

typedef struct		s_packet
{
	struct icmphdr		hdr;
	char				msg[PACKET_SIZE - sizeof(struct icmphdr)];
}					t_packet;

typedef struct		s_ping
{
	int					v;
	int					ttl;
	struct timeval		timeout;
	struct sockaddr		*sock_addr;
	char				ip[INET_ADDRSTRLEN + 1];
	char				*host;
	int					sockfd;
	int					sent;
	int					received;
	size_t				time;
	t_packet			pckt;
	struct msghdr		msg;
	size_t				t1;
	size_t				t2;
	size_t				start;
	size_t				max;
	size_t				min;
	size_t				avg;
	size_t				mdev;
	int					ping_loop;
}					t_ping;

t_ping				ping_s;

int			parser(int ac, char **av);
void		usage();

int			diff_time(size_t t1, size_t t2);
size_t		get_time_now(void);

int			get_ipv4();

int			ping();
void		end_of_ping(int code);
void		statistics();
void		calc_stat();

#endif
