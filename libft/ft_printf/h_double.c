/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_double.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:15:42 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"
#include "libbig.h"

char	*h_a(t_param *param, t_bin *bin)
{
	char	*out;
	char	*mantissa16;
	char	*exponent10;
	size_t	mlen;
	size_t	elen;

	if (bin->exp == FP_ILOGB0)
		bin->exp = 0;
	mantissa16 = get_mantissa16(param, bin);
	exponent10 = ft_itoa(bin->exp);
	if (!mantissa16 || !exponent10)
		return (NULL);
	mlen = ft_strlen(mantissa16);
	elen = ft_strlen(exponent10);
	out = ft_strnew(mlen + 1 + elen + (bin->exp >= 0 ? 1 : 0));
	if (!out)
		return (NULL);
	ft_strcat(param->pre, param->type == t_a ? "0x" : "0X");
	ft_memcpy(out, mantissa16, mlen);
	ft_memcpy(out + mlen, (bin->exp >= 0) ? "p+" : "p", 1 + (bin->exp >= 0));
	ft_memcpy(out + mlen + 1 + (bin->exp >= 0 ? 1 : 0), exponent10, elen);
	free(mantissa16);
	free(exponent10);
	return (out);
}

char	*h_e(t_param *param, t_bin *bin)
{
	char	*out;
	int		i;
	int		exp;
	char	*exponent10;
	char	*mantissa10;

	mantissa10 = get_mantissa10(param, bin, &exp);
	exponent10 = ft_itoa_pad(exp, 2);
	if (!mantissa10 || !exponent10)
		return (NULL);
	i = ft_strlen(mantissa10);
	out = ft_strnew(i + 2 + ft_strlen(exponent10));
	if (!out)
		return (NULL);
	ft_memcpy(out, mantissa10, i);
	if (out[i - 1] == '.' && !param->flags[f_hash])
		--i;
	out[i++] = 'e';
	if (exp >= 0)
		out[i++] = '+';
	ft_strcpy(out + i, exponent10);
	free(exponent10);
	free(mantissa10);
	return (out);
}

char	*h_f(t_param *param, t_bin *bin)
{
	char	*out;
	char	*normal_notation;

	normal_notation = get_normal_notation(param, bin);
	out = ft_strnew(get_length_w_precision(normal_notation, param->precision));
	if (!out)
		return (NULL);
	ft_strcpy(out, normal_notation);
	handle_decimal_precision(out, param);
	if (!param->precision && !param->flags[f_hash])
		out[ft_strfind(out, '.')] = '\0';
	free(normal_notation);
	return (out);
}

/*
**  Style e is used if the exponent from its conversion is less than -4
**  or greater than or equal to the precision.
*/

char	*h_g(t_param *param, t_bin *bin)
{
	int		exp;
	char	*normal_notation;
	char	*scientific_notation;

	if (!param->precision)
		param->precision = 1;
	--(param->precision);
	scientific_notation = h_e(param, bin);
	if (!scientific_notation)
		return (NULL);
	exp = ft_atoi(ft_strchr(scientific_notation, 'e') + 1);
	if (exp < -4 || exp >= param->precision + 1)
		return (scientific_notation);
	free(scientific_notation);
	param->precision -= exp;
	normal_notation = h_f(param, bin);
	if (!normal_notation)
		return (NULL);
	h_g_normal_notation_post(param, normal_notation);
	return (normal_notation);
}

char	*h_double(t_param *param, va_list args)
{
	t_bin	bin;
	char	*out;

	read_double_as_binary(param, args, &bin);
	if (!bin.mantissa)
		return (NULL);
	if ((bin.exp == FP_ILOGBNAN && ft_strfind(bin.mantissa, '1') != -1)
			|| (bin.exp == INT_MAX))
		out = ft_strdup(bin.exp == INT_MAX ? "inf" : "nan");
	else if (param->type == t_a || param->type == t_A)
		out = h_a(param, &bin);
	else if (param->type == t_f || param->type == t_F)
		out = h_f(param, &bin);
	else if (param->type == t_e || param->type == t_E)
		out = h_e(param, &bin);
	else
		out = h_g(param, &bin);
	if (!out)
		return (NULL);
	if (ft_strstr(out, "nan") || ft_strstr(out, "inf"))
		param->flags[f_zero] = 0;
	if (param->type >= DOUBLES_CAPITAL_START && param->type < DOUBLES_END)
		ft_strtoupper(out);
	free(bin.mantissa);
	return (out);
}
