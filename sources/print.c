/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:41:17 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 19:22:12 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void		pr_packet(t_packet *pack)
{
	struct timeval	tv;
	double			triptime;

	if (env.flags & F_QUIET)
		return ;
	gettimeofday(&tv, NULL);
	printf("%d bytes from %s: ", pack->size, pack->src);
	printf("icmp_seq=%d ", pack->seq);
	printf("ttl=%d ", pack->ttl);
	tvsub(&tv, &env.send_time);
	triptime = ((double)tv.tv_sec) * 1000.0 + ((double)tv.tv_usec) / 1000.0;
	printf("time=%.3f ms", triptime);
	if (triptime < env.tmin)
		env.tmin = triptime;
	if (triptime > env.tmax)
		env.tmax = triptime;
	env.tsum += triptime;
	env.sumsq += triptime * triptime;
	printf("\n");
}

static char	*pr_icmp_err_code(struct icmp *icmp)
{
	if (icmp->icmp_type == ICMP_UNREACH)
	{
		if (icmp->icmp_code == ICMP_UNREACH_NET)
			return ("Destination Net Unreachable");
		else if (icmp->icmp_code == ICMP_UNREACH_HOST)
			return ("Destination Host Unreachable");
		else if (icmp->icmp_code == ICMP_UNREACH_PROTOCOL)
			return ("Destination Protocol Unreachable");
		else if (icmp->icmp_code == ICMP_UNREACH_PORT)
			return ("Destination Port Unreachable");
		else if (icmp->icmp_code == ICMP_UNREACH_NEEDFRAG)
			return ("frag needed and DF set");
		else
			return ("Dest Unreachable, Bad Code)");
	}
	else if (icmp->icmp_type == ICMP_TIMXCEED)
	{
		if (icmp->icmp_code == ICMP_TIMXCEED_REASS)
			return ("Frag reassembly time exceeded");
		else
			return ("Time to live exceeded");
	}
	else
		return ("Unknown type.");
}

void		pr_info(struct ip *ip, struct icmp *icmp, int len)
{
	unsigned int	i;

	printf("%d bytes from %s (%s): %s\n", len, env.host,
			inet_ntoa(*(struct in_addr *)&ip->ip_src.s_addr),
			pr_icmp_err_code(icmp));
	printf("IP Hdr Dump:\n");
	i = -1;
	while (++i < sizeof(*ip))
		printf("%s%02x", ((i % 2) ? "" : " "), *((unsigned char *)ip + i));
	printf("\n");
	printf("Vr HL TOS  Len   ID Flg  off TTL");
	printf(" Pro  cks      Src      Dst Data\n");
	printf(" %1x  %1x  %02x %04x %04x",
			ip->ip_v, ip->ip_hl, ip->ip_tos, ip->ip_len, ip->ip_id);
	printf("   %1x %04x", ((ip->ip_off) & 0xe000) >> 13,
		(ip->ip_off) & 0x1fff);
	printf("  %02x  %02x %04x", ip->ip_ttl, ip->ip_p, ip->ip_sum);
	printf(" %s ", inet_ntoa(*(struct in_addr *)&ip->ip_src.s_addr));
	printf(" %s \n", inet_ntoa(*(struct in_addr *)&ip->ip_dst.s_addr));
	printf("ICMP: type %d, code %d, size %d, id 0x%04x, seq 0x%04x",
			icmp->icmp_type, icmp->icmp_code, len, ip->ip_id, icmp->icmp_seq);
	printf("\n");
}
