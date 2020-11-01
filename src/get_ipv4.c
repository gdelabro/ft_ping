/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ipv4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:38:42 by gdelabro          #+#    #+#             */
/*   Updated: 2020/10/30 18:10:38 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		get_ipv4(t_ping *host)
{
	struct addrinfo		ai;
	struct addrinfo		*result;
	struct addrinfo		*addr;
	struct sockaddr_in	*h;

	ft_bzero(&ai, sizeof(ai));
	ai.ai_family = AF_INET;
	ai.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host->host, "http", &ai, &result))
		return (0);
	addr = result;
	while (addr)
	{
		h = (struct sockaddr_in*)addr->ai_addr;
		if (!inet_ntop(AF_INET, (void*)&h->sin_addr,
						host->ip, INET_ADDRSTRLEN))
			return (0);
		addr = addr->ai_next;
		host->sock_addr = (struct sockaddr*)h;
	}
	//freeaddrinfo(result);
	return (1);
}
