/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:27:28 by gdelabro          #+#    #+#             */
/*   Updated: 2020/10/27 18:57:00 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		check_opt(t_ping *host_opt, char **opt, int *i)
{
	int i2;

	i2 = 0;
	if (!ft_strcmp(opt[*i], "-t") && opt[*i + 1])
	{
		host_opt->ttl = ft_atoi(opt[*i + 1]);
		*i += 1;
		return (0);
	}
	if (!ft_strcmp(opt[*i], "-W") && opt[*i + 1])
	{
		host_opt->timeout.tv_sec = ft_atoi(opt[*i + 1]);
		*i += 1;
		return (0);
	}
	while (opt[*i][++i2])
	{
		if (opt[*i][i2] == 'v')
			host_opt->v = 1;
		else if (opt[*i][i2] == 'h')
			usage();
		else
			return (opt[*i][i2]);
	}
	return (0);
}

int		parser(t_ping *host_opt, int ac, char **av)
{
	int i;
	int a;

	ft_bzero(host_opt, sizeof(*host_opt));
	host_opt->ttl = DEFAULT_TTL;
	i = 0;
	a = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			a = check_opt(host_opt, av, &i);
		else if (!host_opt->host)
			host_opt->host = av[i];
		else
			return (0);
		if (a)
		{
			printf("ft_ping: invalid option -- \'%c\'\n", a);
			return (0);
		}
	}
	return (1);
}
