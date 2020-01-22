/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_multiplication.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:44:01 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbig.h"

static size_t	get_bigmult_len(t_big a, t_big b)
{
	return (big_len(a) + big_len(b));
}

static void		big_one_digit_mult(t_big a, t_big out, int b)
{
	int i;
	int rem;

	i = 0;
	rem = 0;
	while (a[i] != EON)
	{
		out[i] = a[i] * b + rem;
		if (out[i] > 9)
		{
			rem = out[i] / 10;
			out[i] %= 10;
		}
		else
			rem = 0;
		++i;
	}
	if (rem)
		out[i] = rem;
}

t_big			big_mult(t_big a, t_big b)
{
	t_big	out;
	int		i;
	int		j;
	t_big	temp;
	t_big	to_free;

	out = bigllup(0);
	temp = bignew(get_bigmult_len(a, b));
	i = 0;
	while (b[i] != EON)
	{
		j = 0;
		while (j < i)
			temp[j++] = 0;
		big_one_digit_mult(a, temp + i, b[i]);
		to_free = out;
		out = big_add(out, temp);
		free(to_free);
		++i;
	}
	free(temp);
	return (out);
}

t_big			big_imult(t_big a, intmax_t b, enum e_free clean)
{
	t_big temp;
	t_big out;

	temp = bigllup(b);
	out = big_mult(a, temp);
	free(temp);
	if (clean != F_NONE)
		free(a);
	return (out);
}
