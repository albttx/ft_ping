/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:17:27 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/22 21:13:26 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"
#include "libnetwork.h"

/*
** IP_HDRINCL must be set on the socket so that the kernel does not attempt 
** to automatically add a default ip header to the packet
*/

int		set_socket_options(int sock)
{
	int		on;
	int		val;
	int		ret[3];

	on = 1;
	val = 255;
	ft_bzero(&ret, sizeof(int) * 3);
	/*ret[0] = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on));*/
	/*ret[0] = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));*/
	/*ret[1] = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));*/
	/*ret[2] = setsockopt(sock, SOL_IP, IP_TTL, &val, sizeof(val));*/
	if (ret[0] == -1 || ret[1] == -1 || ret[3] == -1)
	{
		perror("setsockopt");
		return (-1);
	}
	return (sock);
}

int		create_socket(void)
{
	int					sock;
	/*struct protoent		*proto;*/
	/*if (!(proto = getprotobyname("icmp")))*/
		/*perror("getprotobyname");*/
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	/*sock = socket(AF_INET, SOCK_RAW, proto->p_proto);*/
	if (sock == -1)
	{
		perror("create_socket: socket()");
		exit(EXIT_FAILURE);
	}
	return (set_socket_options(sock));
}
