/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:17:27 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 20:04:03 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"
#include "libnetwork.h"

static int		set_socket_options(int sock)
{
	int		on;

	on = 1;
	setsockopt(sock, IPPROTO_IP, IP_RECVTTL, &on, sizeof(on));
	if (env.ttl > 0)
		setsockopt(sock, IPPROTO_IP, IP_TTL, &env.ttl, sizeof(env.ttl));
	return (sock);
}

int				create_socket(void)
{
	int					sock;

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock == -1)
	{
		perror("create_socket: socket()");
		exit(EXIT_FAILURE);
	}
	return (set_socket_options(sock));
}
