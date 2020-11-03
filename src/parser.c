/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:27:28 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/03 16:57:52 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		check_opt2(char **opt, int *i)
{
	if (!ft_strcmp(opt[*i], "-i") && opt[*i + 1])
		sscanf(opt[*i + 1], "%f", &g_ping.i);
	else if (!ft_strcmp(opt[*i], "-c") && opt[*i + 1])
		g_ping.c = ft_atoi(opt[*i + 1]);
	else if (!ft_strcmp(opt[*i], "-t") && opt[*i + 1])
		g_ping.ttl = ft_atoi(opt[*i + 1]);
	else if (!ft_strcmp(opt[*i], "-W") && opt[*i + 1])
		g_ping.timeout.tv_sec = ft_atoi(opt[*i + 1]);
	else
		return (1);
	if (!ft_strcmp(opt[*i], "-c") && g_ping.c <= 0)
	{
		printf("ft_ping: bad number of packet\n");
		exit(2);
	}
	if (!ft_strcmp(opt[*i], "-i") && g_ping.i < 0.2)
	{
		printf("ft_ping: cannot flood; minimal \
interval allowed for user is 200ms\n");
		exit(2);
	}
	*i += 1;
	return (0);
}

int		check_opt(char **opt, int *i)
{
	int i2;

	i2 = 0;
	if (!check_opt2(opt, i))
		return (0);
	while (opt[*i][++i2])
	{
		if (opt[*i][i2] == 'v')
			g_ping.v = 1;
		else if (opt[*i][i2] == 'h')
			usage();
		else if (opt[*i][i2] == 'q')
			g_ping.q = 1;
		else
			return (opt[*i][i2]);
	}
	return (0);
}

int		parser(int ac, char **av)
{
	int i;
	int a;

	ft_bzero(&g_ping, sizeof(g_ping));
	g_ping.ttl = DEFAULT_TTL;
	g_ping.timeout.tv_sec = 1;
	g_ping.min = 50000000;
	g_ping.i = 1.0;
	i = 0;
	a = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			a = check_opt(av, &i);
		else if (!g_ping.host)
			g_ping.host = av[i];
		else
			return (0);
		if (a)
		{
			printf("ft_ping: invalid option -- \'%c\'\n", a);
			return (0);
		}
	}
	return (g_ping.host ? 1 : 0);
}
