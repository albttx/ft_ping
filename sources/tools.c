/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 13:09:44 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 20:09:32 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

void				tvsub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) < 0)
	{
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

unsigned short		in_cksum(unsigned short *addr, int len)
{
	register int			sum;
	unsigned short			answer;
	register unsigned short	*w;
	register int			nleft;

	sum = 0;
	answer = 0;
	w = addr;
	nleft = len;
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1)
	{
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}
