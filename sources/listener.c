/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:22:30 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 19:56:49 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ping.h"

static void		recv_loop(int sock, struct msghdr *msg_h)
{
	ssize_t				cc;
	char				packet[MAX_PACKET_LEN];
	struct iovec		iov;

	iov.iov_base = packet;
	iov.iov_len = sizeof(packet);
	msg_h->msg_iov = &iov;
	msg_h->msg_iovlen = 1;
	while (42)
	{
		ft_bzero(&packet, sizeof(packet));
		cc = recvmsg(sock, msg_h, 0);
		if (cc == -1)
		{
			perror("recvmsg");
			return ;
		}
		if (read_packet(packet, cc) > 0)
			env.nreceived++;
		alarm((u_int)1);
	}
}

int				listener(int sock)
{
	struct sockaddr_in	sin;
	struct msghdr		msg_h;
	char				cmsg[MAX_PACKET_LEN];

	ft_bzero(&sin, sizeof(sin));
	ft_bzero(&cmsg, sizeof(cmsg));
	msg_h.msg_name = &sin;
	msg_h.msg_namelen = sizeof(sin);
	msg_h.msg_control = &cmsg;
	msg_h.msg_controllen = sizeof(cmsg);
	msg_h.msg_flags = 0;
	recv_loop(sock, &msg_h);
	return (1);
}
