/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 20:07:48 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int				ft_ping(char *hostname)
{
	if (!ping_opt.hostip)
	{
		printf("ping: cannot resolve %s: Unknown host\n", hostname);
		return (-1);
	}
	ping_opt.host = hostname;
	printf("PING %s (%s): %d data bytes\n", hostname, ping_opt.hostip,
			(ping_opt.datalen < 48) ? 48 : ping_opt.datalen );
	ping_opt.sock = create_socket();
	if (ping_opt.sock == -1)
		return (-1);
	signal(SIGALRM, pinger);
	signal(SIGINT, finished);
	pinger(0);
	listener(ping_opt.sock);
	free(ping_opt.hostip);
	return (1);
}
