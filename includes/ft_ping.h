/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:24 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 20:21:21 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include "libnetwork.h"

# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>

# include <signal.h>

# define	DEFDATA_LEN	(64 - 8)
# define	MAX_IP_LEN	60
# define	MAX_ICMP_LEN	76
# define	MAX_PACKET_LEN	(65536 - 60 - 8)

# define	MIN_PACKET_LEN (sizeof(struct iphdr) + sizeof(struct icmphdr))

typedef enum		e_pingflags
{
	F_NONE =		0,
	F_VERBOSE =		1,
	F_QUIET =		2,
}					t_pingflags;

typedef struct		s_pingopt
{
	int				sock;
	char			*host;
	char			*hostip;
	long			ntransmitted;
	long			nreceived;
	int				count;
	int				datalen;
	int				id;
	double			tmin;
	double			tmax;
	double			tsum;
	struct timeval	send_time;
	t_pingflags		flags;
}					t_pingopt;

typedef struct		s_packet
{
	int				size;
	char			host[INET_ADDRSTRLEN];
	int				ttl;
	int				seq;
}					t_packet;

t_pingopt			ping_opt;

int					ft_ping(char *host);
int					create_socket(void);
int					parser(char **av);

void				pinger(int singal);
int					listener(int sock);
void				read_packet(char packet[], int len);

void				finished(int signal);
unsigned short		in_cksum(unsigned short *addr, int len);
void				tvsub(struct timeval *out, struct timeval *in);
void				print_ip_header(char *buff);
void				print_icmp_packet(char *buff);

#endif
