/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_addition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:41:29 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbig.h"

static size_t	get_bigadd_len(t_big a, t_big b)
{
	size_t lena;
	size_t lenb;

	lena = big_len(a);
	lenb = big_len(b);
	return ((lena > lenb ? lena : lenb) + 1);
}

static void		finish_off(t_big x, t_big out, int i, char rem)
{
	while (*x != EON)
	{
		out[i] = *(x++) + rem;
		rem = 0;
		++i;
	}
}

t_big			big_add(t_big a, t_big b)
{
	t_big	out;
	int		i;
	char	rem;

	out = bignew(get_bigadd_len(a, b));
	i = 0;
	rem = 0;
	while (*a != EON && *b != EON)
	{
		out[i] = *(a++) + *(b++) + rem;
		if (out[i] > 9)
		{
			rem = 1;
			out[i] %= 10;
		}
		else
			rem = 0;
		++i;
	}
	finish_off(a, out, i, rem);
	finish_off(b, out, i, rem);
	return (out);
}

t_big			big_iadd(t_big a, intmax_t b)
{
	t_big temp;
	t_big out;

	temp = bigllup(b);
	out = big_add(a, temp);
	free(temp);
	return (out);
}
