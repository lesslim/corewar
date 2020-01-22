/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_helpers_common.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:59:25 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

enum e_size	choose_size(t_param *param)
{
	enum e_size	id;
	size_t		size;

	id = 0;
	size = sizeof(int);
	if (param->length[l_l] == 1 && (size = sizeof(long)))
		id = LONG;
	if (param->length[l_l] > 1 && sizeof(long long) > size
		&& (size = sizeof(long long)))
		id = LLONG;
	if (param->length[l_z] && sizeof(size_t) > size
		&& (size = sizeof(size_t)))
		id = SIZE_T;
	if (param->length[l_j] && sizeof(intmax_t) > size
		&& (size = sizeof(intmax_t)))
		id = INTMAX;
	if (param->length[l_t] && sizeof(ptrdiff_t) > size)
		id = PTRDIFF;
	return (id);
}

int			find_insignificant_zeros(char *s)
{
	int	i;
	int	first_zero;

	i = 0;
	first_zero = -1;
	while (s[i])
	{
		if (s[i] != '0')
			first_zero = -1;
		else if (first_zero == -1)
			first_zero = i;
		++i;
	}
	return (first_zero);
}

void		remove_trailing_zeros(char *s)
{
	int	first_zero;

	first_zero = find_insignificant_zeros(s);
	if (first_zero == -1)
		return ;
	s[first_zero] = '\0';
}

int			get_base(t_param *param)
{
	if (param->type == t_d || param->type == t_u)
		return (10);
	if (param->type == t_o)
		return (8);
	return (16);
}

void		signed_prepend(int negative, t_param *param)
{
	if (negative)
		param->pre[0] = '-';
	else if (param->flags[1])
		param->pre[0] = '+';
	else if (param->flags[2])
		param->pre[0] = ' ';
}
