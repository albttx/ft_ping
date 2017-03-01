/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:07 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/01 11:45:48 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int		usage(char *f)
{
	printf("Usage: [-c count] [-t TTL] [-q Quiet] [-v Verbose] %s host\n", f);
	return (-1);
}

static void		init(void)
{
	g_env.sock = 0;
	g_env.hostip = NULL;
	g_env.ntransmitted = 0;
	g_env.nreceived = 0;
	g_env.sumsq = 0;
	g_env.datalen = DEFDATA_LEN - 20;
	g_env.flags = 0;
	g_env.count = -1;
	g_env.id = getpid() & 0xFFFF;
	g_env.tmin = 999999999.0;
	g_env.tmax = 0.0;
	g_env.tsum = 0.0;
	g_env.ttl = -1;
	ft_bzero(&g_env.send_time, sizeof(struct timeval));
}

int				main(int ac, char **av)
{
	if (ac < 2)
		return (usage(av[0]));
	init();
	parser(av);
	ft_ping(av[ac - 1]);
	return (0);
}
