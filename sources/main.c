/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:07 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/04 17:30:52 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int		usage(void)
{
	printf("Usage: %s host\n", __FILE__);
	return (-1);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (usage());
	ft_ping(av[1]);
	return (0);
}
