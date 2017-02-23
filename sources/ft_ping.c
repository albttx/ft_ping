/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/23 21:03:19 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"
#include "libnetwork.h"
#include <netinet/ip_icmp.h>

#include <sys/signal.h>

void			pinger(int signal)
{
	char				*packet;
	struct sockaddr_in	sin;
	struct icmp			*icmp_packet;

	size_t size = sizeof(struct iphdr) + sizeof(struct icmphdr);
	printf("PING size= %ld\n", size);
	printf("icmp= %ld\n", sizeof(struct icmp));
	/*size_t size = ping_opt.packlen;*/
	packet = ft_strnew(size);
	ft_bzero(&sin, sizeof(struct sockaddr_in));
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = inet_addr(ping_opt.hostip);

	icmp_packet = (struct icmp *)packet;
	icmp_packet->icmp_type = ICMP_ECHO;
	icmp_packet->icmp_code = 0;
	icmp_packet->icmp_seq = ping_opt.ntransmitted;
	icmp_packet->icmp_cksum = in_cksum((unsigned short *)icmp_packet, size);

	/*if (sendto(ping_opt.sock, packet, size, 0, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) == -1)*/
	ssize_t ret = sendto(ping_opt.sock, packet, size, 0, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));
	if (!ret)
	{
		perror("sendto");
		return ;
	}
	printf("-- Sending %ld bytes -- \n", ret);
	alarm(1);
	/*free(packet);*/
}

void		print_msg(struct msghdr *msg_h)
{
	struct cmsghdr		*cmsg;
	struct sockaddr_in	*sin;
	char				ip[INET_ADDRSTRLEN];
	int					ttl;

	sin = msg_h->msg_name;
	inet_ntop(AF_INET, &(sin->sin_addr), ip, INET_ADDRSTRLEN);
	cmsg = CMSG_FIRSTHDR(msg_h);
	while (cmsg)
	{
		if (cmsg->cmsg_level == IPPROTO_IP && cmsg->cmsg_type == IP_TTL)
			ttl = *(int *)CMSG_DATA(cmsg);
		cmsg = CMSG_NXTHDR(msg_h, cmsg);
	}
	printf("%s", GREEN);
	printf("%d bytes from %s: ", ping_opt.datalen, ip);
	printf("icmp_seq=%ld ", ping_opt.ntransmitted++);
	printf("ttl=%d ", ttl);
	printf("\n");
	printf("%s", DEFAULT);
}

int			listener(int sock)
{
	struct sockaddr_in	sin;
	struct msghdr		msg_h;
	struct iovec		iov;
	struct icmphdr		icmp_h;
	char				cmsg[100];

	ft_bzero(&sin, sizeof(sin));
	msg_h.msg_name = &sin;
	msg_h.msg_namelen = sizeof(sin);

	iov.iov_base = &icmp_h;
	iov.iov_len = sizeof(icmp_h);
	msg_h.msg_iov = &iov;
	msg_h.msg_iovlen = 1;

	msg_h.msg_control = &cmsg;
	msg_h.msg_controllen = sizeof(cmsg);
	msg_h.msg_flags = 0;
	while (42)
	{
		/*if (recvmsg(sock, &msg_h, 0) == -1)*/
		ssize_t ret = recvmsg(sock, &msg_h, 0);
		if (ret == -1)
		{
			perror("recvmsg");
			return (-1);
		}
		printf("recv:%ld ", ret);
		print_msg(&msg_h);
		alarm((u_int)1);
	}
	return (1);
}

static void		init(void)
{
	ping_opt.sock = 0;
	ping_opt.hostip = NULL;
	ping_opt.ntransmitted = 0;
	ping_opt.datalen = DEFDATALEN;
	ping_opt.packlen = ping_opt.datalen + MAXIPLEN + MAXICMPLEN;
	printf("PING: datalen = %d\n", ping_opt.datalen);
	printf("PING: packlen = %d\n", ping_opt.packlen);
}

void			finished(int signal)
{
	printf("%s\n", DEFAULT);
	exit(EXIT_SUCCESS);
}

int				ft_ping(char *hostname, int packetsize)
{
	init();
	ping_opt.hostip = hostname_to_ip(hostname);
	if (!ping_opt.hostip)
	{
		printf("ping: cannot resolve %s: Unknown host\n", hostname);
		return (-1);
	}
	printf("PING %s (%s): %d data bytes\n", hostname, ping_opt.hostip, packetsize);
	ping_opt.sock = create_socket();
	if (ping_opt.sock == -1)
		return (-1);
	signal(SIGALRM, pinger);
	signal(SIGINT, finished);
	pinger(0);
	listener(ping_opt.sock);
	free(ping_opt.hostip);
	return (1);
}
