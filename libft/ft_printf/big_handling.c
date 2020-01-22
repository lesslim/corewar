/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:43:27 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbig.h"

t_big	bignew(size_t len)
{
	t_big out;

	out = (t_big)malloc(len + 1);
	ft_memset(out, EON, len + 1);
	return (out);
}

t_big	bigllup(intmax_t x)
{
	t_big	out;
	size_t	i;
	size_t	len;

	len = (size_t)get_num_len_base(x, 10);
	out = bignew(len);
	i = 0;
	while (i < len)
	{
		out[i] = x % 10;
		x /= 10;
		i++;
	}
	return (out);
}

t_big	bigbinup(char *bin)
{
	t_big out;
	t_big to_free;

	out = bigllup(0);
	while (*bin)
	{
		out = big_imult(out, 2, F_ALL);
		if (*bin == '1')
		{
			to_free = out;
			out = big_iadd(out, 1);
			free(to_free);
		}
		++bin;
	}
	return (out);
}

size_t	big_len(t_big a)
{
	size_t	out;

	out = 0;
	while (a[out] != EON)
		out++;
	return (out);
}

char	*bigtoa(t_big x, enum e_free clean)
{
	size_t	len;
	int		i;
	char	*out;

	len = big_len(x);
	out = ft_strnew(len);
	i = len;
	out[i] = '\0';
	while (--i >= 0)
		out[i] = x[len - i - 1] + '0';
	if (clean != F_NONE)
		free(x);
	return (out);
}
