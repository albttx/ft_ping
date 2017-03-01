/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:20:45 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/01 11:48:32 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void			pinger(int signal)
{
	char				packet[g_env.datalen];
	struct sockaddr_in	sin;
	struct icmp			*icmp;
	ssize_t				cc;

	ft_bzero(&packet, sizeof(packet));
	ft_bzero(&sin, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = inet_addr(g_env.hostip);
	icmp = (struct icmp *)packet;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_id = g_env.id;
	icmp->icmp_seq = g_env.ntransmitted++;
	icmp->icmp_cksum = in_cksum((u_short *)icmp, g_env.datalen + 8);
	gettimeofday(&(g_env.send_time), NULL);
	cc = sendto(g_env.sock, packet, g_env.datalen + 8, 0,
			(struct sockaddr *)&sin, sizeof(struct sockaddr_in));
	if (!cc)
	{
		perror("sendto");
		return ;
	}
	alarm(1);
	(void)signal;
}
