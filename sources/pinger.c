/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pinger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:20:45 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 19:59:49 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void			pinger(int signal)
{
	char				packet[ping_opt.datalen];
	struct sockaddr_in	sin;
	struct icmp			*icmp_packet;
	ssize_t				cc;

	ft_bzero(&packet, sizeof(packet));
	ft_bzero(&sin, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = inet_addr(ping_opt.hostip);

	icmp_packet = (struct icmp *)packet;
	icmp_packet->icmp_type = ICMP_ECHO;
	icmp_packet->icmp_code = 0;
	icmp_packet->icmp_id = ping_opt.id;
	icmp_packet->icmp_seq = ping_opt.ntransmitted++;
	icmp_packet->icmp_cksum = in_cksum((unsigned short *)icmp_packet, ping_opt.datalen + 8);
	gettimeofday(&(ping_opt.send_time), NULL);
	cc = sendto(ping_opt.sock, packet, ping_opt.datalen + 8, 0, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));
	if (!cc)
	{
		perror("sendto");
		return ;
	}
	alarm(1);
}
