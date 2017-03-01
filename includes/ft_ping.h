/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:24 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/01 11:46:48 by ale-batt         ###   ########.fr       */
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

# define DEFDATA_LEN (64 - 8)
# define MAX_IP_LEN 60
# define MAX_ICMP_LEN 76
# define MAX_PACKET_LEN (65536 - 60 - 8)
# define MIN_PACKET_LEN 28

typedef enum		e_pingflags
{
	F_NONE = 0,
	F_VERBOSE = 1,
	F_QUIET = 2,
}					t_pingflags;

typedef struct		s_env
{
	int				sock;
	char			*host;
	char			*hostip;
	long			ntransmitted;
	long			nreceived;
	int				count;
	int				ttl;
	double			sumsq;
	int				datalen;
	int				id;
	double			tmin;
	double			tmax;
	double			tsum;
	struct timeval	send_time;
	t_pingflags		flags;
}					t_env;

typedef struct		s_packet
{
	int				size;
	char			src[INET_ADDRSTRLEN];
	int				ttl;
	int				seq;
	char			dst[INET_ADDRSTRLEN];
	int				tos;
	int				id;
}					t_packet;

t_env				g_env;

int					ft_ping(char *host);
int					create_socket(void);
int					parser(char **av);

void				pinger(int singal);
int					listener(int sock);
int					read_packet(char packet[], int len);

void				finished(int signal);
unsigned short		in_cksum(unsigned short *addr, int len);
void				tvsub(struct timeval *out, struct timeval *in);

void				pr_packet(t_packet *pack);
void				pr_info(struct ip *ip, struct icmp *icmp, int len);

#endif
