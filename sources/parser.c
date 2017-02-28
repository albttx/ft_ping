/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:59:20 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 20:05:02 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ping.h"

static void		opt_packsize(char *str_nb)
{
	env.datalen = (long)ft_atoi(str_nb);
	if (env.datalen < (long)MIN_PACKET_LEN)
	{
		printf("ping: illegal packet size.\n");
		exit(EXIT_FAILURE);
	}
	else if (env.datalen > (long)MAX_PACKET_LEN)
	{
		printf("ping: packet size too large.\n");
		exit(EXIT_FAILURE);
	}
}

static void		opt_count(char *str_nb)
{
	env.count = ft_atoi(str_nb);
	if (env.count <= 0)
	{
		printf("ping: bad number of packets to transmit.\n");
		exit(EXIT_FAILURE);
	}
}

static void		opt_ttl(char *str_nb)
{
	env.ttl = ft_atoi(str_nb);
	if (env.ttl <= 0)
	{
		printf("ping: can't set unicast time-to-live: Invalid argument\n");
		exit(EXIT_FAILURE);
	}
}

int				parser(char **av)
{
	int		y;

	y = 0;
	while (av[y])
	{
		if (ft_strequ(av[y], "-v"))
			env.flags |= F_VERBOSE;
		else if (ft_strequ(av[y], "-s"))
			opt_packsize(av[++y]);
		else if (ft_strequ(av[y], "-q"))
			env.flags |= F_QUIET;
		else if (ft_strequ(av[y], "-c"))
			opt_count(av[++y]);
		else if (ft_strequ(av[y], "-t"))
			opt_ttl(av[++y]);
		else
		{
			env.hostip = hostname_to_ip(av[y]);
			if (env.hostip != NULL)
				break ;
		}
		y++;
	}
	return (1);
}
