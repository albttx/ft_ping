/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/20 19:51:11 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int			ft_ping(char *hostname, int packetsize)
{
	/*int					ret;*/
	char				*hostip;
	/*struct addrinfo		*res;*/
	/*struct addrinfo		hints;*/

	hostip = hostname_to_ip(hostname);
	if (!hostip)
	{
		printf("ping: cannot resolve %s: Unknown host\n", hostname);
		return (-1);
	}
	printf("PING %s (%s): %d data bytes\n", hostname, hostip, packetsize);

	struct protoent *proto;
	proto = getprotobyname("icmp");
	int sock = socket(AF_INET, SOCK_RAW, proto->p_proto);
	perror("socket");
	printf("sock = %d\n", sock);

	/*ft_bzero(&hints, sizeof(hints));*/
	/*ft_bzero(&res, sizeof(*res));*/
	/*hints.ai_family = PF_UNSPEC;*/
	/*hints.ai_socktype = SOCK_STREAM;*/
	/*ret = getaddrinfo(NULL, host, &hints, &res);*/
	/*ret = getaddrinfo(hostip, "http", &hints, &res);*/
	/*printf("ret = %d \n", ret);*/
	return (1);
}
