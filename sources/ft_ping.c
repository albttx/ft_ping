/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/27 19:48:39 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int				ft_ping(char *hostname)
{
	if (!env.hostip)
	{
		printf("ping: cannot resolve %s: Unknown host\n", hostname);
		return (-1);
	}
	env.host = hostname;
	printf("PING %s (%s): %d data bytes", hostname, env.hostip,
			(env.datalen < 56) ? 56 : env.datalen );
	if (env.flags & F_VERBOSE)
		printf(", id 0x%04x = %d", env.id, env.id);
	printf("\n");
	env.sock = create_socket();
	if (env.sock == -1)
		return (-1);
	signal(SIGALRM, pinger);
	signal(SIGINT, finished);
	pinger(0);
	listener(env.sock);
	free(env.hostip);
	return (1);
}
