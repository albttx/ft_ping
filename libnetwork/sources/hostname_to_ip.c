/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname_to_ip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 17:43:18 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/21 11:56:48 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnetwork.h"
#include "libft.h"

char	*hostname_to_ip(const char *hostname)
{
	char			*ip;
	struct hostent	*he;
	struct in_addr	**addr_list;

	ip = ft_strnew(MAX_LEN_IPV4 + 1);
	he = gethostbyname(hostname); 
	if (he == NULL)
	{
		perror("hostname_to_ip: gethostbyname()");
		return (NULL);
	}
	addr_list = (struct in_addr **)he->h_addr_list;
	ft_strcpy(ip, inet_ntoa(*addr_list[0]));
	return (ip);
}
