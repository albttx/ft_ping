/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:23:07 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/23 16:12:19 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int		usage(char *file)
{
	printf("Usage: %s host\n", file);
	return (-1);
}

int				main(int ac, char **av)
{
	if (ac != 2)
		return (usage(av[0]));
	if (ft_strequ(av[1], "localhost"))
		ft_ping(ft_strdup(LOCALHOST), 42);
	else
		ft_ping(ft_strdup(av[1]), 42);
	return (0);
}
