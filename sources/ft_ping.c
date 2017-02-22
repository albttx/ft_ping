/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/22 21:27:22 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"
#include "libnetwork.h"
#include <netinet/ip_icmp.h>

#include <sys/signal.h>

void		print_packet(char *packet, struct sockaddr_in *from)
{
	struct ip		*ip_packet;
	struct iphdr	*ip_header;
	struct icmp		*icmp_packet;
	struct icmphdr	*icmp_header;
	u_int16_t		ttl;

	icmp_packet = (struct icmp *)packet;
	ip_packet = (struct ip *)packet;
	ttl = ip_packet->ip_ttl;
	icmp_packet->icmp_seq = ping_opt.ntransmitted++;

	ip_header = (struct iphdr *)packet;
	printf("%d bytes from %s: ", ntohs(ip_header->tot_len), inet_ntoa(from->sin_addr));
	printf("icmp_seq=%d ", icmp_packet->icmp_seq);
	printf("ttl=%d ", ttl);
	/*printf("time=%g ms", );*/
	printf("\n");
}

int			pinger(int sock, char *hostip)
{
	char				*packet;
	size_t				size;
	struct sockaddr_in	connection;
	struct icmp			*icmp_packet;

	size = sizeof(struct iphdr) + sizeof(struct icmphdr);
	ft_bzero(&connection, sizeof(struct sockaddr_in));
	packet = ft_strnew(size);
	
	connection.sin_family = AF_INET;
	/*connection.sin_port = 0;*/
	connection.sin_addr.s_addr = inet_addr(hostip);
	/*connection.sin_addr.s_addr = htonl(INADDR_ANY);*/
	/*memcpy(&connection.sin_addr, h->h_addr, sizeof(connection.sin_addr));*/

	icmp_packet = (struct icmp *)packet;
	icmp_packet->icmp_type      = ICMP_ECHO;
	icmp_packet->icmp_code      = 0;
	icmp_packet->icmp_cksum     = in_cksum((unsigned short *)icmp_packet, size);

	/*icmp_packet->icmp_cksum     = in_cksum((unsigned short *)icmp_packet, sizeof(packet));*/
	if (sendto(sock, packet, size, 0, (struct sockaddr *)&connection, sizeof(struct sockaddr_in)) == -1)
	{
		perror("sendto");
		return (-1);
	}
	return (1);
}

int			listener(int sock)
{
	char				*packet_recv;
	struct sockaddr_in	from;
	socklen_t			fromlen;
	/*struct msghdr		msg;*/
	size_t				size;

	size = sizeof(struct iphdr) + sizeof(struct icmphdr);
	/*while (42)*/
	{
		packet_recv = ft_strnew(size);
		fromlen = sizeof(from);
		if (recvfrom(sock, packet_recv, size, 0, (struct sockaddr *)&from, &fromlen) == -1)
		{
			perror("recvfrom");
			return (-1);
		}
		print_packet(packet_recv, &from);
	}
	return (1);
}

int			loop(int sock, char *hostip)
{
	int i = 0;

	while (i < 5)
	{
		pinger(sock, hostip);
		listener(sock);
		sleep(1);
		i++;
	}
	return 1;
}

void		init(void)
{
	ping_opt.ntransmitted = 0;
}

int			ft_ping(char *hostname, int packetsize)
{
	char				*hostip;
	int					sock;

	init();
	hostip = hostname_to_ip(hostname);
	if (!hostip)
	{
		printf("ping: cannot resolve %s: Unknown host\n", hostname);
		return (-1);
	}
	printf("PING %s (%s): %d data bytes\n", hostname, hostip, packetsize);
	sock = create_socket();
	if (sock == -1)
		return (-1);
	loop(sock, hostip);
	free(hostip);
	return (1);
}
