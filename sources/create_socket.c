/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:17:27 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/21 20:56:08 by ale-batt         ###   ########.fr       */
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

	on = 1;
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) == -1)
	{
		perror("setsockopt");
		return (-1);
	}
	return (sock);
}

int		create_socket(void)
{
	int					sock;

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock == -1)
	{
		perror("create_socket: socket()");
		exit(EXIT_FAILURE);
	}
	/*return (set_socket_options(sock));*/
	return (sock);
}
