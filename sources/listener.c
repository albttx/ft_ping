/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:22:30 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 20:09:24 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int				listener(int sock)
{
	struct sockaddr_in	sin;
	struct msghdr		msg_h;
	struct iovec		iov;
	char				packet[MAX_PACKET_LEN];
	char				cmsg[MAX_PACKET_LEN];
	ssize_t				cc;

	ft_bzero(&packet, sizeof(packet));
	ft_bzero(&sin, sizeof(sin));
	ft_bzero(&cmsg, sizeof(cmsg));
	msg_h.msg_name = &sin;
	msg_h.msg_namelen = sizeof(sin);

	iov.iov_base = packet;
	iov.iov_len = sizeof(packet);
	msg_h.msg_iov = &iov;
	msg_h.msg_iovlen = 1;

	msg_h.msg_control = &cmsg;
	msg_h.msg_controllen = sizeof(cmsg);
	msg_h.msg_flags = 0;
	while (42)
	{
		cc = recvmsg(sock, &msg_h, 0);
		if (cc == -1)
		{
			perror("recvmsg");
			return (-1);
		}
		read_packet(packet, cc);
		ping_opt.nreceived++;
		/*print_msg(&msg_h);*/
		alarm((u_int)1);
	}
	return (1);
}
