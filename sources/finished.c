/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finished.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:05:24 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/28 19:46:39 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"

void			finished(int signal)
{
	double	variance;
	double	avg;

	printf("--- %s ping statistics ---\n", env.host);
	variance = 0.0;
	avg = env.tsum / env.nreceived;
	if (env.nreceived > 1)
		variance = env.sumsq / env.nreceived - avg * avg;
	printf("%ld packets transmitted, ", env.ntransmitted);
	printf("%ld packets received, ", env.nreceived);
	printf("%ld%% packet loss\n",
		((env.ntransmitted - env.nreceived) * 100) / env.ntransmitted);
	if (env.tmin < env.tmax)
	{
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms",
				env.tmin,
				env.tsum / (env.nreceived),
				env.tmax,
				ft_sqrt(variance));
		printf("\n");
	}
	(void)signal;
	exit(EXIT_SUCCESS);
}
