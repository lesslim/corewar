/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_unsigned.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 17:56:21 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

static int			get_unum_len_base(uintmax_t n, int base)
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

static uintmax_t	read_uinteger(t_param *param, va_list args)
{
	uintmax_t	out;
	enum e_size	id;

	id = choose_size(param);
	if (id == INT)
		out = va_arg(args, unsigned int);
	else if (id == LONG)
		out = va_arg(args, unsigned long);
	else if (id == LLONG)
		out = va_arg(args, unsigned long long);
	else if (id == SIZE_T)
		out = va_arg(args, size_t);
	else if (id == INTMAX)
		out = va_arg(args, uintmax_t);
	else
		out = va_arg(args, ptrdiff_t);
	if (id || !param->length[0])
		return (out);
	return (param->length[0] & 1 ? (unsigned short)out : (unsigned char)out);
}

static void			llutoa_base
	(uintmax_t n, int base, char *out, unsigned int len)
{
	if (n == 0)
		out[0] = BASE[0];
	out[len] = '\0';
	while (n != 0)
	{
		out[len - 1] = BASE[n % base];
		n /= base;
		len--;
	}
}

static void			manage_prepend(t_param *param, uintmax_t n, int len)
{
	if (param->type == t_p
			|| ((param->type == t_x || param->type == t_X)
				&& param->flags[f_hash]
				&& n))
		ft_strcpy(param->pre, (param->type == t_X) ? "0X" : "0x");
	if (param->type == t_o && param->flags[f_hash] && param->precision <= len
			&& (n || !param->precision))
		ft_strcpy(param->pre, "0");
}

char				*h_unsigned(t_param *param, va_list args)
{
	uintmax_t	n;
	char		*out;
	int			len;
	int			base;
	int			i;

	base = get_base(param);
	n = read_uinteger(param, args);
	len = get_unum_len_base(n, base);
	manage_prepend(param, n, len);
	out = ft_strnew((param->precision > len) ? param->precision : len);
	if (!out)
		return (NULL);
	i = 0;
	while (i < (param->precision - len))
		out[i++] = '0';
	llutoa_base(n, base, out + i, len);
	if (param->type == t_X)
		ft_strtoupper(out);
	if (!n && !param->precision)
		ft_strclr(out);
	return (out);
}
