/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 17:30:26 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/04 18:44:33 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	interate_addrs(struct addrinfo *res)
{
	struct addrinfo		*ptr;
	char				dst[100];

	ptr = res;
	while (ptr != NULL)
	{
		ft_bzero(dst, 100);
		/*inet_ntop(AF_INET, (void *)(ptr->ai_addr), dst, ptr->ai_addrlen);*/
		inet_ntop(AF_INET, (void *)(ptr->ai_addr), dst, ptr->ai_addrlen);
		printf("dst= %s\n", dst);
		ptr = ptr->ai_next;
	}
}

void	ft_ping(char *host)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	int					ret;

	ft_bzero(&hints, sizeof(hints));
	ft_bzero(&res, sizeof(*res));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	/*ret = getaddrinfo(NULL, host, &hints, &res);*/
	ret = getaddrinfo(host, "http", &hints, &res);
	printf("ret = %d \n", ret);
	interate_addrs(res);
}
