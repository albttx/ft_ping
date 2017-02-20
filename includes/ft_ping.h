/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:24 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/20 19:27:45 by ale-batt         ###   ########.fr       */
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

typedef struct	s_packet
{
	int			nb_bytes;
	char		*ip;
	int			icmp_seq;
	int			ttl;
	time_t		time;
}				t_packet;

int				ft_ping(char *host, int packetsize);

#endif
