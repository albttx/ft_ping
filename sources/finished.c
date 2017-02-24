/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finished.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:05:24 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/24 20:34:34 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"

void			finished(int signal)
{
	printf("--- %s ping statistics ---\n", ping_opt.host);
	printf("%ld packets transmitted, ", ping_opt.ntransmitted);
	printf("%ld packets received, ", ping_opt.nreceived);
	printf("%ld%% packet loss\n",
			((ping_opt.ntransmitted - ping_opt.nreceived) * 100) / 
			ping_opt.ntransmitted);
	printf("round-trip min/avg/max/stddev = %g/%g/%g/%g",
			ping_opt.tmin,
			ping_opt.tsum / (ping_opt.nreceived),
			ping_opt.tmax,
			ping_opt.tsum);
	printf("\n");
	exit(EXIT_SUCCESS);
}
