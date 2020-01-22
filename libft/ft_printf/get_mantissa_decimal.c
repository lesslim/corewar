/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mantissa_decimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:47:35 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

static int	isnotdotzero(char c)
{
	return (c != '.' && c != '0');
}

static void	initialize_gm10(char *normal_notation, int *nz, int *exp)
{
	int d;

	d = ft_strfind(normal_notation, '.');
	*nz = ft_strfindif(normal_notation, &isnotdotzero);
	if (*nz < 0)
		*nz = d - 1;
	*exp = d - *nz - (d > *nz);
}

static void	copy_integer(char *dest, char *normal_notation)
{
	*dest = *normal_notation;
	*(dest + 1) = '.';
}

static int	copy_fraction
	(char *dest, char *normal_notation, t_param *param)
{
	int	i;
	int dot;

	i = 0;
	dot = 0;
	while (i <= param->precision + 1 && normal_notation[i])
	{
		if (normal_notation[i] == '.')
		{
			dot = 1;
			++i;
			continue ;
		}
		dest[i - dot] = normal_notation[i];
		++i;
	}
	i -= dot;
	return (i);
}

/*
**	Searching for the first non-zero digit and copying it to the mantissa.
**	Then the dot is placed and the rest is copied.
*/

char		*get_mantissa10(t_param *param, t_bin *bin, int *exp)
{
	char	*normal_notation;
	char	*out;
	int		nz;
	int		i;

	normal_notation = get_normal_notation(param, bin);
	out = ft_strnew(3 + param->precision);
	if (!normal_notation || !out)
		return (NULL);
	initialize_gm10(normal_notation, &nz, exp);
	copy_integer(out, normal_notation + nz);
	i = copy_fraction(out + 2, normal_notation + nz + 1, param);
	while (i <= param->precision + 1)
		out[2 + i++] = '0';
	handle_decimal_precision(out, param);
	if (ft_strfind(param->pre, '1') != -1)
	{
		ft_strcpy(out, ".0");
		handle_decimal_precision(out, param);
		++(*exp);
	}
	if ((param->type == t_g || param->type == t_G) && !param->flags[f_hash])
		remove_trailing_zeros(out);
	free(normal_notation);
	return (out);
}
