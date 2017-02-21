/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/21 21:40:20 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"
#include "libnetwork.h"
#include <netinet/ip_icmp.h>

#include <sys/signal.h>

unsigned short in_cksum(unsigned short *addr, int len)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = addr;
    register int nleft = len;
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1)
    {
      sum += *w++;
      nleft -= 2;
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1)
    {
      *(u_char *) (&answer) = *(u_char *) w;
      sum += answer;
    }
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
    sum += (sum >> 16);             /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return (answer);
}

struct icmphdr		create_icmp_header(void)
{
	struct icmphdr	icmp_header;

	icmp_header.type = ICMP_ECHO;
	icmp_header.un.echo.sequence = 50;
	icmp_header.un.echo.id = 42;
	/*icmp_header.checksum =*/
		/*in_cksum((unsigned short *)&icmp_header, sizeof(struct icmphdr));*/
	return (icmp_header);
}

void		read_packet_recv(char *recv_buff)
{
	char			*cp;
	struct iphdr	*ip_reply;
	struct icmp		*icmp_reply;
	struct icmphdr	*icmp_header;
	u_int16_t		ttl;

	/*icmp_reply = sizeof(struct iphdr) + (struct icmp *)recv_buff;*/
	icmp_reply = (struct icmp *)recv_buff;
	ttl = icmp_reply->icmp_hun.ih_rtradv.irt_lifetime;
	/*u_int16_t irt_lifetime;*/
	printf("ttl = %d\n", ttl);

	ip_reply = (struct iphdr*)recv_buff;
	/*cp = (char *)&ip_reply->saddr;*/
	/*printf("Received %d byte reply from %u.%u.%u.%u:\n", ntohs(ip_reply->tot_len), cp[0]&0xff,cp[1]&0xff,cp[2]&0xff,cp[3]&0xff);*/
	/*printf("ID: %d\n", ntohs(ip_reply->id));*/
	/*printf("TTL: %d\n", ip_reply->ttl);*/
}

int			loop(int sock, char *hostip)
{
	int					size;
	char				*packet;
	char				*recv_buff;
	/*struct iphdr		*ip_header;*/
	/*struct icmphdr		*icmp_header;*/
	struct icmp			*icmp_packet;
	struct sockaddr_in	connection;

	size = sizeof(struct iphdr) + sizeof(struct icmphdr);
	packet = ft_strnew(size);
	recv_buff = ft_strnew(size);

	/*ip_header = (struct iphdr *)packet;*/
	/*icmp_header = (struct icmphdr *)(packet + sizeof(struct iphdr));*/

	/*ip_header->ihl         = 5;*/
    /*ip_header->version     = 4;*/
    /*ip_header->tot_len     = size;*/
    /*ip_header->protocol    = IPPROTO_ICMP;*/
    /*ip_header->saddr       = inet_addr("10.12.12.18");*/
    /*ip_header->daddr       = inet_addr(hostip);*/
    /*ip_header->check       = in_cksum((unsigned short *)ip_header, sizeof(struct iphdr)); */

	/*icmp_header->type      = ICMP_ECHO;*/
	/*icmp_header->checksum  = in_cksum((unsigned short *)icmp_header, sizeof(struct icmphdr));*/

	ft_bzero(&connection, sizeof(struct sockaddr_in));
	connection.sin_family       = AF_INET;
	/*connection.sin_addr.s_addr  = ip_header->daddr;*/
	connection.sin_addr.s_addr = inet_addr(hostip);

	icmp_packet = (struct icmp *)packet;
	icmp_packet->icmp_type      = ICMP_ECHO;
	icmp_packet->icmp_cksum     = in_cksum((unsigned short *)icmp_packet, sizeof(packet));

	int ret_send = sendto(sock, packet, sizeof(packet), 0, (struct sockaddr *)&connection, sizeof(struct sockaddr_in));
	if (ret_send == -1)
		perror("sendto");
	printf("ret_send = %d\n", ret_send);

	/*int ret_send = sendto(sock, packet, ip_header->tot_len, 0, (struct sockaddr *)&connection, sizeof(struct sockaddr));*/
	/*perror("sendto");*/
	/*printf("ret_send = %d, Sent %d byte packet to %s\n", ret_send, ip_header->tot_len, hostip);*/

	while (42)
	{
		struct sockaddr_in	from;
		socklen_t			fromlen;
		/*socklen_t addrlen = sizeof(connection);*/
	   
		fromlen = sizeof(from);


		ssize_t ret_recv = recvfrom(sock, packet, sizeof(packet), 0, (struct sockaddr *)&from, &fromlen);
		if (ret_recv < 0)
		{
			perror("recvfrom");
			continue;
		}
		read_packet_recv(packet);
	}
	/*recvfrom(sock, recv_buff, sizeof(struct iphdr) + sizeof(struct icmphdr), 0, (struct sockaddr *)&connection, &addrlen);*/


	return (1);
}

int			ft_ping(char *hostname, int packetsize)
{
	char				*hostip;
	int					sock;

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
