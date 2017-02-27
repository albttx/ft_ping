/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:12:53 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/27 18:54:47 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

#define ERR_BAD_ID -1
#define ERR_BAD_CKSUM -2
#define ERR_NOT_ECHOREPLY -3

static void	fill_packet(t_packet *p, struct ip *ip, struct icmp *icmp, int l)
{
	ft_bzero(p, sizeof(t_packet));
	inet_ntop(AF_INET, &(ip->ip_src), p->src, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(ip->ip_dst), p->dst, INET_ADDRSTRLEN);
	p->size = l;
	p->seq = icmp->icmp_seq;
	p->ttl = ip->ip_ttl;
}

int			read_packet(char packet[], int len)
{
	struct ip		*ip;
	struct icmp		*icmp;
	t_packet		pack;

	ip = (struct ip *)(packet);
	icmp = (void *)ip + sizeof(struct ip);
	if (icmp->icmp_id != env.id)
	{
		if (env.flags & F_VERBOSE)
			printf("ft_ping: packet received %d bytes id invalid", len);
		return (ERR_BAD_ID);
	}
	fill_packet(&pack, ip, icmp, len);
	if (icmp->icmp_type != ICMP_ECHOREPLY && env.flags & F_VERBOSE)
	{
		pr_info(ip, icmp, len);
		return (ERR_NOT_ECHOREPLY);
	}
	if (in_cksum((unsigned short *)&icmp->icmp_cksum, len) && env.flags & F_VERBOSE)
	{
		puts("ft_ping: BAD CHECKSUM");
		return (ERR_BAD_CKSUM);
	}
	else
		pr_packet(&pack);
	if (env.count != -1 && env.count == (icmp->icmp_seq+1))
		finished(0);
	return (1);
}
