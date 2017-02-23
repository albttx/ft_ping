/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:24 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/23 12:22:49 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include "libnetwork.h"

# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

# include <signal.h>

typedef struct	s_pingopt
{
	int			sock;
	char		*hostip;
	long		ntransmitted;
}				t_pingopt;

t_pingopt		ping_opt;

int				ft_ping(char *host, int packetsize);
int				create_socket(void);

unsigned short	in_cksum(unsigned short *addr, int len);
void			print_ip_header(char *buff);
void			print_icmp_packet(char *buff);

#endif
