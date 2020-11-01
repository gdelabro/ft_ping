/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 23:27:28 by gdelabro          #+#    #+#             */
/*   Updated: 2020/11/01 19:26:09 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

int		check_opt(char **opt, int *i)
{
	int i2;

	i2 = 0;
	if (!ft_strcmp(opt[*i], "-t") && opt[*i + 1])
	{
		ping_s.ttl = ft_atoi(opt[*i + 1]);
		*i += 1;
		return (0);
	}
	if (!ft_strcmp(opt[*i], "-W") && opt[*i + 1])
	{
		ping_s.timeout.tv_sec = ft_atoi(opt[*i + 1]);
		*i += 1;
		return (0);
	}
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
	return (1);
}
