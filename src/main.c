/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:47:22 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/03 16:57:35 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void	usage(void)
{
	printf("Usage: ./ft_ping [-hvq] [-t ttl] [-W timeout] [-c count] \
[-i interval] destination\n");
	exit(2);
}

int		main(int ac, char **av)
{
	if (ac == 1 || !parser(ac, av))
		usage();
	if ((g_ping.sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		printf("ft_ping: socket: Operation not \
permitted(you may want to sudo)\n");
		exit(2);
	}
	if (!get_ipv4())
	{
		printf("ft_ping: %s: Name or service not known\n", g_ping.host);
		return (2);
	}
	printf("PING %s (%s) 56(84) bytes of data.\n", g_ping.host, g_ping.ip);
	signal(SIGINT, &end_of_ping);
	signal(SIGALRM, &end_of_ping);
	ping();
	return (0);
}
