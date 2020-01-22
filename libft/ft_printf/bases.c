/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:32:43 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libbig.h"
#include "handle_helpers.h"

static void	bin2hex_write(char *padded_binary, char *out, size_t padded_bin_len)
{
	size_t	i;
	int		temp;

	i = 0;
	temp = 0;
	while (i < padded_bin_len)
	{
		temp += ((padded_binary[i] == '1') ? (0x08 >> i % 4) : 0);
		++i;
		if (!(i % 4))
		{
			out[i / 4 - 1] = BASE[temp];
			temp = 0;
		}
	}
}

char		*bin2hex(char *binary, int padding)
{
	char	*s;
	size_t	padded_bin_len;
	size_t	bin_len;
	char	*out;

	bin_len = ft_strlen(binary);
	padded_bin_len = !(bin_len % 4) ? bin_len : (bin_len + 4 - bin_len % 4);
	s = ft_strnew(padded_bin_len);
	if (padding == PAD_LEFT)
	{
		ft_memset(s, '0', padded_bin_len - bin_len);
		ft_memcpy(s + padded_bin_len - bin_len, binary, bin_len);
	}
	else
	{
		ft_memcpy(s, binary, bin_len);
		ft_memset(s + bin_len, '0', padded_bin_len - bin_len);
	}
	out = ft_strnew(padded_bin_len / 4);
	bin2hex_write(s, out, padded_bin_len);
	free(s);
	return (out);
}

char		*binary_to_decimal(char *integer, char *fraction)
{
	char	*out;
	char	*integer10;
	char	*fraction10;

	if (!integer || !fraction)
		return (NULL);
	integer10 = bigtoa(bigbinup(integer), F_ALL);
	fraction10 = binary_fraction_to_decimal(fraction);
	if (!integer10 || !fraction10)
		return (NULL);
	out = ft_strnew(ft_strlen(integer10) + 1 + ft_strlen(fraction10));
	if (out)
		ft_strcpy(ft_stpcpy(ft_stpcpy(out, integer10), "."), fraction10);
	free(integer10);
	free(fraction10);
	return (out);
}

int			get_num_len_base(intmax_t n, int base)
{
	int	out;

	if (!n)
		return (1);
	out = 0;
	while (n != 0)
	{
		n /= base;
		out++;
	}
	return (out);
}

void		read_double_as_binary(t_param *param, va_list args, t_bin *bin)
{
	double		x;
	long double	lx;

	if (param->length[l_L])
	{
		lx = va_arg(args, long double);
		bin->exp = ft_ilogbl(lx);
		bin->mantissa = get_mantissa_binary_long(lx);
	}
	else
	{
		x = va_arg(args, double);
		bin->exp = ft_ilogb(x);
		bin->mantissa = get_mantissa_binary(x, bin->exp);
	}
	if (bin->exp != FP_ILOGBNAN)
		signed_prepend(((param->length[l_L]) ? lx : x) < 0, param);
}
