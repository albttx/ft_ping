/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:07 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 19:31:24 by ale-batt         ###   ########.fr       */
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
	env.sock = 0;
	env.hostip = NULL;
	env.ntransmitted = 0;
	env.nreceived = 0;
	env.sumsq = 0;
	env.datalen = DEFDATA_LEN - 20;
	env.flags = 0;
	env.count = -1;
	env.id = getpid() & 0xFFFF;
	env.tmin = 999999999.0;
	env.tmax = 0.0;
	env.tsum = 0.0;
	env.ttl = -1;
	ft_bzero(&env.send_time, sizeof(struct timeval));
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
