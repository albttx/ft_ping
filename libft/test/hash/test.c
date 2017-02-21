/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 16:26:10 by ale-batt          #+#    #+#             */
/*   Updated: 2016/11/02 15:07:48 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

t_hash	*create_data(void)
{
	t_hash *hash;

	hash = NULL;
	ft_add_hash(&hash, "key1", "val1");
	ft_add_hash(&hash, "key2", "val2");
	ft_add_hash(&hash, "key3", "val3");
	return (hash);
}

void	test_add_values(void **state)
{
	t_hash *hash;
	t_hash *tmp;
	(void) state;

	hash = create_data();
	tmp = hash;
	while (tmp)
	{
		assert_non_null(tmp);
		assert_non_null(tmp->key);
		assert_non_null(tmp->value);
		tmp = tmp->next;
	}
}

void	test_free_values(void **state)
{
	t_hash *hash;
	(void) state;

	hash = create_data();
	ft_free_hash(&hash);
	assert_null(hash);
}

void	test_find_values(void **state)
{
	t_hash	*hash;
	char	*ret;

	hash = create_data();
	ret = ft_get_value_hash(hash, "key2");
	assert_string_equal(ret, "val2");

	ret = ft_get_key_hash(hash, "val3");
	assert_string_equal(ret, "key3");

	ret = ft_get_key_hash(hash, "val not exist");
	assert_null(ret);
}

void	test_remove_values(void **state)
{
	t_hash 	*hash;
	int		len;

	hash = create_data();
	len = ft_len_hash(hash);

	ft_remove_key_hash(&hash, "key_not_exist");
	assert_int_equal(len, ft_len_hash(hash));
	ft_remove_key_hash(&hash, "key2");
	assert_int_equal(--len, ft_len_hash(hash));
	ft_remove_key_hash(&hash, "key1");
	assert_int_equal(--len, ft_len_hash(hash));
	ft_remove_key_hash(&hash, "key3");
	assert_int_equal(--len, ft_len_hash(hash));
}

int		main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_add_values),
		cmocka_unit_test(test_free_values),
		cmocka_unit_test(test_find_values),
		cmocka_unit_test(test_remove_values),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
