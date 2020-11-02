/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:27:28 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/02 18:24:56 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		check_opt2(char **opt, int *i)
{
	if (!ft_strcmp(opt[*i], "-i") && opt[*i + 1])
		sscanf(opt[*i + 1], "%f", &ping_s.i);
	else if (!ft_strcmp(opt[*i], "-c") && opt[*i + 1])
		ping_s.c = ft_atoi(opt[*i + 1]);
	else if (!ft_strcmp(opt[*i], "-t") && opt[*i + 1])
		ping_s.ttl = ft_atoi(opt[*i + 1]);
	else if (!ft_strcmp(opt[*i], "-W") && opt[*i + 1])
		ping_s.timeout.tv_sec = ft_atoi(opt[*i + 1]);
	else
		return (1);
	if (!ft_strcmp(opt[*i], "-c") && ping_s.c <= 0)
	{
		printf("ft_ping: bad number of packet\n");
		exit(2);
	}
	if (!ft_strcmp(opt[*i], "-i") && ping_s.i < 0.2)
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
			ping_s.v = 1;
		else if (opt[*i][i2] == 'h')
			usage();
		else
			return (opt[*i][i2]);
	}
	return (0);
}

int		parser(int ac, char **av)
{
	int i;
	int a;

	ft_bzero(&ping_s, sizeof(ping_s));
	ping_s.ttl = DEFAULT_TTL;
	ping_s.timeout.tv_sec = 1;
	ping_s.min = 50000000;
	ping_s.i = 1.0;
	i = 0;
	a = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			a = check_opt(av, &i);
		else if (!ping_s.host)
			ping_s.host = av[i];
		else
			return (0);
		if (a)
		{
			printf("ft_ping: invalid option -- \'%c\'\n", a);
			return (0);
		}
	}
	return (ping_s.host ? 1 : 0);
}
