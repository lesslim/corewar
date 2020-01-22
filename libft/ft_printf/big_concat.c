/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_concat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:42:12 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbig.h"

/*
**	Don't forget that t_big is little endian.
*/

t_big	big_concat(t_big a, t_big b)
{
	t_big	out;
	size_t	lena;
	size_t	lenb;

	lena = big_len(a);
	lenb = big_len(b);
	out = bignew(lena + lenb);
	ft_memcpy(out, a, lena);
	ft_memcpy(out + lena, b, lenb);
	return (out);
}

t_big	big_iconcat(t_big a, intmax_t b, enum e_free clean)
{
	t_big temp;
	t_big out;

	temp = bigllup(b);
	out = big_concat(a, temp);
	free(temp);
	if (clean != F_NONE)
		free(a);
	return (out);
}
