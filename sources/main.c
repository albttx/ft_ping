/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:07 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 20:28:16 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int		usage(char *file)
{
	printf("Usage: %s host\n", file);
	return (-1);
}

static void		init(void)
{
	ping_opt.sock = 0;
	ping_opt.hostip = NULL;
	ping_opt.ntransmitted = 0;
	ping_opt.nreceived = 0;
	ping_opt.datalen = MIN_PACKET_LEN;
	ping_opt.flags = 0;
	ping_opt.count = -1;
	ping_opt.id = getuid();
	ping_opt.tmin = 999999999.0;
	ping_opt.tmax = 0.0;
	ping_opt.tsum = 0.0;
	ft_bzero(&ping_opt.send_time, sizeof(struct timeval));
}

int				main(int ac, char **av)
{
	if (ac < 2)
		return (usage(av[0]));
	init();
	parser(av);
	ft_ping(av[ac-1]);
	return (0);
}
