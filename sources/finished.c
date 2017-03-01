/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finished.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:05:24 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/01 11:45:48 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"

void			finished(int signal)
{
	double	variance;
	double	avg;

	printf("--- %s ping statistics ---\n", g_env.host);
	variance = 0.0;
	avg = g_env.tsum / g_env.nreceived;
	if (g_env.nreceived > 1)
		variance = g_env.sumsq / g_env.nreceived - avg * avg;
	printf("%ld packets transmitted, ", g_env.ntransmitted);
	printf("%ld packets received, ", g_env.nreceived);
	printf("%ld%% packet loss\n",
		((g_env.ntransmitted - g_env.nreceived) * 100) / g_env.ntransmitted);
	if (g_env.tmin < g_env.tmax)
	{
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms",
				g_env.tmin,
				g_env.tsum / (g_env.nreceived),
				g_env.tmax,
				ft_sqrt(variance));
		printf("\n");
	}
	(void)signal;
	exit(EXIT_SUCCESS);
}
