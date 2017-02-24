/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:41:17 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 20:29:07 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void		pr_packet(t_packet *pack)
{
	struct timeval	tv;
	double			triptime;

	if (ping_opt.flags & F_QUIET)
		return ;
	gettimeofday(&tv, NULL);
	printf("%d bytes from %s: ", pack->size, pack->host);
	printf("icmp_seq=%d ", pack->seq);
	printf("ttl=%d ", pack->ttl);
	tvsub(&tv, &ping_opt.send_time);
	triptime = ((double)tv.tv_sec) * 1000.0 + ((double)tv.tv_usec) / 1000.0;
	printf("time=%g ms", triptime);
	if (triptime < ping_opt.tmin)
		ping_opt.tmin = triptime;
	if (triptime > ping_opt.tmax)
		ping_opt.tmax = triptime;
	ping_opt.tsum += triptime;
	printf("\n");
}

void			read_packet(char packet[], int len)
{
	struct ip		*ip;
	struct icmp		*icmp;
	int				csfailed;
	t_packet		pack;

	ip = (struct ip *)(packet);
	icmp = (void *)ip + sizeof(struct ip);
	if (icmp->icmp_type != ICMP_ECHOREPLY)
		return ;
	if (icmp->icmp_id != ping_opt.id)
		return ;
	csfailed = in_cksum((unsigned short *)&icmp->icmp_cksum, len);
	if (csfailed)
		puts("PING: BAD CHECKSUM");
	ft_bzero(&pack.host, sizeof(pack.host));
	inet_ntop(AF_INET, &(ip->ip_src), pack.host, INET_ADDRSTRLEN);
	pack.size = len;
	pack.seq = icmp->icmp_seq;
	pack.ttl = ip->ip_ttl;
	pr_packet(&pack);
	if (ping_opt.count != -1 && ping_opt.count == (icmp->icmp_seq+1))
		finished(0);
}
