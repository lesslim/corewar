/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_signed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:55:00 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

static void			lltoa_base
	(intmax_t n, int base, char *out, unsigned int len)
{
	if (n == 0)
		out[0] = BASE[0];
	out[len] = '\0';
	while (n != 0)
	{
		out[len - 1] = BASE[n % base * ((n > 0) - (n < 0))];
		n /= base;
		len--;
	}
}

static intmax_t		read_integer(t_param *param, va_list args)
{
	intmax_t		out;
	enum e_size		id;

	id = choose_size(param);
	if (id == INT)
		out = va_arg(args, int);
	else if (id == LONG)
		out = va_arg(args, long);
	else if (id == LLONG)
		out = va_arg(args, long long);
	else if (id == SIZE_T)
		out = va_arg(args, ssize_t);
	else if (id == INTMAX)
		out = va_arg(args, intmax_t);
	else
		out = va_arg(args, ptrdiff_t);
	if (id || !param->length[0])
		return (out);
	return (param->length[l_h] & 1 ? (short)out : (char)out);
}

char				*h_signed(t_param *param, va_list args)
{
	intmax_t	n;
	char		*out;
	int			i;
	int			len;
	int			base;

	base = get_base(param);
	n = read_integer(param, args);
	len = get_num_len_base(n, base);
	out = ft_strnew((param->precision > len) ? param->precision : len);
	if (!out)
		return (NULL);
	i = 0;
	signed_prepend(n < 0, param);
	while (i < (param->precision - len))
		out[i++] = '0';
	lltoa_base(n, base, out + i, len);
	if (!n && !param->precision)
		ft_strclr(out);
	return (out);
}
