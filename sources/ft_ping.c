/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/01 11:45:48 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int				ft_ping(char *hostname)
{
	if (!g_env.hostip)
	{
		printf("ping: cannot resolve %s: Unknown host\n", hostname);
		return (-1);
	}
	g_env.host = hostname;
	printf("PING %s (%s): %d data bytes", hostname, g_env.hostip,
			(g_env.datalen < 56) ? 56 : g_env.datalen);
	if (g_env.flags & F_VERBOSE)
		printf(", id 0x%04x = %d", g_env.id, g_env.id);
	printf("\n");
	g_env.sock = create_socket();
	if (g_env.sock == -1)
		return (-1);
	signal(SIGALRM, pinger);
	signal(SIGINT, finished);
	pinger(0);
	listener(g_env.sock);
	free(g_env.hostip);
	return (1);
}
