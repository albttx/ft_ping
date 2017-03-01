/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:12:53 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/01 11:45:48 by ale-batt         ###   ########.fr       */
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

static int	verification(struct icmp *icmp, struct ip *ip, int len)
{
	if (icmp->icmp_type != ICMP_ECHOREPLY)
	{
		if (g_env.flags & F_VERBOSE)
			pr_info(ip, icmp, len);
		return (ERR_NOT_ECHOREPLY);
	}
	if (icmp->icmp_id != g_env.id)
	{
		if (g_env.flags & F_VERBOSE)
			printf("ft_ping: packet received %d bytes id invalid\n", len);
		return (ERR_BAD_ID);
	}
	if (in_cksum((unsigned short *)&icmp->icmp_cksum, len))
	{
		if (g_env.flags & F_VERBOSE)
			printf("ft_ping: BAD CHECKSUM\n");
		return (ERR_BAD_CKSUM);
	}
	return (1);
}

int			read_packet(char packet[], int len)
{
	struct ip		*ip;
	struct icmp		*icmp;
	t_packet		pack;

	ip = (struct ip *)(packet);
	icmp = (void *)ip + sizeof(*ip);
	fill_packet(&pack, ip, icmp, len);
	if (verification(icmp, ip, len) < 0)
		return (-1);
	pr_packet(&pack);
	if (g_env.count != -1 && g_env.count == (icmp->icmp_seq + 1))
		finished(0);
	return (1);
}
