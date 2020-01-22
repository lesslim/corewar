/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_fraction_to_decimal.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:45:01 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libbig.h"
#include "bases.h"

static t_big	big_leading_zeros(t_big a, size_t *n, enum e_free clean)
{
	t_big	out;
	size_t	lena;

	if (*n <= 0)
		return (a);
	lena = big_len(a);
	out = bignew(lena + *n);
	ft_memcpy(out, a, lena);
	ft_memset(out + lena, 0, *n);
	if (clean != F_NONE)
		free(a);
	*n = 0;
	return (out);
}

static void		initialize_bftd
	(char *bin, int *i, t_big *preout, size_t *leading_zeros)
{
	*i = (int)ft_strlen(bin);
	while (*i - 1 >= 0 && bin[*i - 1] == '0')
		--i;
	if (i <= 0)
		return ;
	*preout = bignew(0);
	*leading_zeros = 0;
}

char			*binary_fraction_to_decimal(char *bin)
{
	int		i;
	char	*out;
	t_big	preout;
	t_big	to_free;
	size_t	leading_zeros;

	initialize_bftd(bin, &i, &preout, &leading_zeros);
	if (i <= 0)
		return (ft_itoa(0));
	while (--i >= 0)
	{
		if (bin[i] == '1')
		{
			preout = big_leading_zeros(preout, &leading_zeros, F_ALL);
			preout = big_iconcat(preout, 1, F_ALL);
		}
		to_free = preout;
		preout = big_imult(preout, 5, F_NONE);
		if (bin[i] == '0' && big_len(to_free) == big_len(preout))
			++leading_zeros;
		free(to_free);
	}
	preout = big_leading_zeros(preout, &leading_zeros, F_ALL);
	out = bigtoa(preout, F_ALL);
	return (out);
}
