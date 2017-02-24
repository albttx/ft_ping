/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 11:59:20 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 20:00:15 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ping.h"

static void		opt_packsize(char *str_nb)
{
	ping_opt.datalen = (long)ft_atoi(str_nb);
	if (ping_opt.datalen < (long)MIN_PACKET_LEN)
	{
		printf("ping: illegal packet size.\n");
		exit(EXIT_FAILURE);
	}
	else if (ping_opt.datalen > (long)MAX_PACKET_LEN)
	{
		printf("ping: packet size too large.\n");
		exit(EXIT_FAILURE);
	}
}

static void		opt_count(char *str_nb)
{
	ping_opt.count = ft_atoi(str_nb);
	if (ping_opt.count <= 0)
	{
		printf("ping: bad number of packets to transmit.\n");
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
			ping_opt.flags |= F_VERBOSE;
		else if (ft_strequ(av[y], "-s"))
			opt_packsize(av[++y]);
		else if (ft_strequ(av[y], "-q"))
			ping_opt.flags |= F_QUIET;
		else if (ft_strequ(av[y], "-c"))
			opt_count(av[++y]);
		else
		{
			ping_opt.hostip = hostname_to_ip(av[y]);
			if (ping_opt.hostip != NULL)
				break ;
		}
		y++;
	}
	return (1);
}
