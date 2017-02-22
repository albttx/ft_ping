/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_icmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:41:32 by ale-batt          #+#    #+#             */
/*   Updated: 2017/02/22 16:37:40 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "libft.h"
#include "libnetwork.h"
#include <netinet/ip_icmp.h>

void	print_ip_header(char *buff)
{
	struct iphdr		*ip_header;
	struct sockaddr_in	source;
	struct sockaddr_in	dest;
	socklen_t			iphdr_len;

	memset(&source, 0, sizeof(source));
	memset(&dest, 0, sizeof(dest));
	ip_header = (struct iphdr *)buff;
	iphdr_len = ip_header->ihl * 4;

	printf("IP Header\n");
	printf("   |-IP Version        : %d\n", (unsigned int)ip_header->version);
	printf("   |-IP Header Length  : %d DWORDS or %d Bytes\n", (unsigned int)ip_header->ihl, ((unsigned int)(ip_header->ihl))*4);
	printf("   |-Type Of Service   : %d\n", (unsigned int)ip_header->tos);
	printf("   |-IP Total Length   : %d  Bytes(Size of Packet)\n", ntohs(ip_header->tot_len));
	printf("   |-Identification    : %d\n", ntohs(ip_header->id));
	/*printf("   |-Reserved ZERO Field   : %d\n",(unsigned int)ip_header->ip_reserved_zero);*/
	/*printf("   |-Dont Fragment Field   : %d\n",(unsigned int)ip_header->ip_dont_fragment);*/
	/*printf("   |-More Fragment Field   : %d\n",(unsigned int)ip_header->ip_more_fragment);*/
	printf("   |-TTL               : %d\n", (unsigned int)ip_header->ttl);
	printf("   |-Protocol          : %d\n", (unsigned int)ip_header->protocol);
	printf("   |-Checksum          : %d\n", ntohs(ip_header->check));
	printf("   |-Source IP         : %s\n", inet_ntoa(source.sin_addr));
	printf("   |-Destination IP    : %s\n", inet_ntoa(dest.sin_addr));
}

void	print_icmp_packet(char *buff)
{
	socklen_t			iphdr_len;
	struct iphdr		*ip_header;
	struct icmphdr		*icmp_header;
   
	ip_header = (struct iphdr *)buff;
	iphdr_len = ip_header->ihl * 4;
	icmp_header = (struct icmphdr *)(buff + iphdr_len);

    printf("ICMP Header\n");
    printf("   |-Type : %d", (unsigned int)(icmp_header->type));
             
    if((unsigned int)(icmp_header->type) == 11) 
        printf("  (TTL Expired)\n");
    else if((unsigned int)(icmp_header->type) == ICMP_ECHOREPLY) 
        printf("  (ICMP Echo Reply)\n");
    printf("   |-Code : %d\n", (unsigned int)(icmp_header->code));
    printf("   |-Checksum : %d\n", ntohs(icmp_header->checksum));
	/*printf("   |-ID       : %d\n", ntohs(icmp_header->id));*/
	/*printf("   |-Sequence : %d\n", ntohs(icmp_header->sequence));*/
    printf("\n");
}
