/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:46:48 by ale-batt          #+#    #+#             */
/*   Updated: 2016/11/02 16:15:27 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int ge_sort(void *a, void *b)
{
	return ((*(int *)a) > (*(int *)b));
}

int le_sort(void *a, void *b)
{
	return ((*(int *)a) < (*(int *)b));
}

void	print_list(t_list *lst)
{
	t_list *tmp = lst;
	int		n;

	while (tmp)
	{
		n = *(int *)(tmp->content);
		printf("n = %d\n", n);
		tmp = tmp->next;
	}
}

int	*arr_list_sorted(int len)
{
	int *arr;
	int i = 0;

	arr = (int *)malloc(sizeof(int) * (len + 1));
	while (i < len)
	{
		arr[i] = i + 1;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

int	*arr_list_random(int len)
{
	int		*arr;
	int		rdm;
	int		i;
   	
	i = 0;
	arr = (int *)malloc(sizeof(int) * (len + 1));
	srand(time(NULL));
	while (i < len)
	{
		rdm = (rand() % 1000) + 1;
		arr[i] = rdm;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

int	*arr_list_always_equal(int len)
{
	int		*arr;
	int		i;
   	
	i = 0;
	arr = (int *)malloc(sizeof(int) * (len + 1));
	while (i < len)
	{
		arr[i] = 42;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

t_list	*create_list(int *arr)
{
	t_list	*list;
	int 	i = 1;

	list = NULL;
	i = 0;
	while (arr[i] != 0)
	{
		ft_lstadd(&list, ft_lstnew(&(arr[i]), sizeof(int *)));
		i++;
	}
	return (list);
}

int is_sort(t_list *list)
{
	t_list *tmp;
	int a, b;

	tmp = list;
	while (tmp->next)
	{
		a = *(int *)(tmp->content);
		b = *(int *)(tmp->next->content);
		if (a > b)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}


