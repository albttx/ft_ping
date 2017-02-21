/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:22:56 by ale-batt          #+#    #+#             */
/*   Updated: 2016/11/02 16:40:32 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

int			ge_sort(void *a, void *b);
int			le_sort(void *a, void *b);
int			*arr_list_sorted(int len);
int			*arr_list_random(int len);
t_list		*create_list(int *arr);
int			is_sort(t_list *list);
void		print_list(t_list *lst);
int			*arr_list_always_equal(int len);

void	test_sort_values(void **state)
{
	t_list *list;

	list = create_list(arr_list_sorted(10));
	is_sort(list);
	ft_lstsort(&list, ge_sort);
	is_sort(list);
}

void	test_rand_values(void **state)
{
	t_list *list;

	list = create_list(arr_list_random(10));
	assert_false(is_sort(list));
	ft_lstsort(&list, ge_sort);
	assert_true(is_sort(list));
}

void	test_always_equal_values(void **state)
{
	t_list *list;

	list = create_list(arr_list_always_equal(10));
	ft_lstsort(&list, ge_sort);
	assert_true(is_sort(list));
}

void	test_one_value_only(void **state)
{
	t_list *list;

	list = create_list(arr_list_always_equal(1));
	ft_lstsort(&list, ge_sort);
	assert_true(is_sort(list));
}

void	test_two_value(void **state)
{
	t_list *list;
	int i_list_a[3] = {42, 43, 0};
	int i_list_b[3] = {43, 42, 0};

	list = create_list(i_list_a);
	ft_lstsort(&list, ge_sort);
	assert_true(is_sort(list));
	
	list = create_list(i_list_b);
	ft_lstsort(&list, ge_sort);
	assert_true(is_sort(list));
}

void	test_big_list(void **state)
{
	t_list *list;

	list = create_list(arr_list_random(1000));
	ft_lstsort(&list, ge_sort);
	assert_true(is_sort(list));
}

int		test_lstsort(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_sort_values),
		cmocka_unit_test(test_rand_values),
		cmocka_unit_test(test_always_equal_values),
		cmocka_unit_test(test_one_value_only),
		cmocka_unit_test(test_two_value),
		cmocka_unit_test(test_big_list),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
