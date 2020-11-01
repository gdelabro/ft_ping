/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:47:22 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/01 18:46:19 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

void	usage()
{
	printf("Usage: ./ft_ping [-hv] [-t ttl] [-W timeout]\
destination\n");
	exit(2);
}

int		main(int ac, char **av)
{
	if (ac == 1 || !parser(ac, av))
		usage();
	if ((ping_s.sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		printf("%s\n", strerror(errno));
		printf("ft_ping: socket: Operation not permitted(you may want to sudo)\n");
		exit(2);
	}
	if (!get_ipv4())
	{
		printf("ft_ping: %s: Name or service not known\n", av[1]);
		return (2);
	}
	printf("PING %s (%s) 56(84) bytes of data.\n", ping_s.host, ping_s.ip);
	signal(SIGINT, &end_of_ping);
	ping();
	return (0);
}
