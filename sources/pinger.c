/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:20:45 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 19:47:59 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void			pinger(int signal)
{
	char				packet[env.datalen];
	struct sockaddr_in	sin;
	struct icmp			*icmp_packet;
	ssize_t				cc;

	ft_bzero(&packet, sizeof(packet));
	ft_bzero(&sin, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = inet_addr(env.hostip);
	icmp_packet = (struct icmp *)packet;
	icmp_packet->icmp_type = ICMP_ECHO;
	icmp_packet->icmp_id = env.id;
	icmp_packet->icmp_seq = env.ntransmitted++;
	icmp_packet->icmp_cksum = in_cksum((u_short *)icmp_packet, env.datalen + 8);
	gettimeofday(&(env.send_time), NULL);
	cc = sendto(env.sock, packet, env.datalen + 8, 0,
			(struct sockaddr *)&sin, sizeof(struct sockaddr_in));
	if (!cc)
	{
		perror("sendto");
		return ;
	}
	alarm(1);
	(void)signal;
}
