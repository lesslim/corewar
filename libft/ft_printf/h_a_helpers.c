/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_a_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:57:14 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

static void		up_one16(char *s, int i)
{
	long	temp;

	while (--i >= 0)
	{
		if (s[i] == '.')
			continue ;
		if ((temp = ft_strfind(BASE, s[i])) < 15)
		{
			s[i] = BASE[temp + 1];
			return ;
		}
		else
			s[i] = '0';
	}
}

static size_t	calculate_len(size_t intlen, size_t frlen, int precision)
{
	if (precision <= 0)
		return (intlen + frlen + 1);
	return (intlen + frlen + 1 +
			(((ssize_t)frlen > precision) ? frlen : precision));
}

/*
**	Getting to the first char after the dot in the first loop;
**	Then proceeding to the char that needs to be evaluated to determine
**	which way to round.
*/

static void		handle_precision16(char *s, t_param *param)
{
	int i;
	int	j;

	if (param->precision < 0)
		param->precision = find_insignificant_zeros(s + 2);
	if (param->precision < 0)
		return ;
	i = 0;
	while (s[i++] != '.')
	{
	}
	j = 0;
	while (j < param->precision)
	{
		if (!s[i + j])
			s[i + j] = '0';
		++j;
	}
	if (!s[i + j])
		return ;
	if (ft_strfind(BASE, s[i + j]) >= 9)
		up_one16(s, i + j);
	s[i + j] = '\0';
}

char			*get_mantissa16(t_param *param, t_bin *bin)
{
	char	*out;
	char	*fraction16;

	fraction16 = bin2hex(bin->mantissa + 1, PAD_RIGHT);
	if (!fraction16)
		return (NULL);
	out = ft_strnew(calculate_len(1, ft_strlen(fraction16), param->precision));
	if (!out)
		return (NULL);
	ft_memcpy(out, bin->mantissa, 1);
	out[1] = '.';
	ft_strcpy(out + 2, fraction16);
	free(fraction16);
	handle_precision16(out, param);
	if (!param->precision && !param->flags[f_hash])
		out[ft_strfind(out, '.')] = '\0';
	return (out);
}
