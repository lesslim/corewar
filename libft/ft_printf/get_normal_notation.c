/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_notation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:48:31 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

static void	case_exp_negative
	(char **integer, char **fraction, t_param *param, t_bin *bin)
{
	*integer = ft_strnew(1);
	*fraction = ft_strnew((param->length[l_L] ? 63 : 52) + bin->exp * -1);
	if (!(*integer) || !(*fraction))
		return ;
	(*integer)[0] = '0';
	ft_memset(*fraction, '0', bin->exp * -1 - 1);
	ft_memcpy(*fraction + bin->exp * -1 - 1, bin->mantissa,
			(param->length[l_L] ? 64 : 53));
}

/*
**	"Small" means less than the number of bits.
*/

static void	case_exp_small
	(char *integer, char **fraction, t_param *param, t_bin *bin)
{
	ft_memcpy(integer, bin->mantissa, 1 + bin->exp);
	*fraction = ft_strnew((param->length[l_L] ? 63 : 52) - bin->exp);
	if (!(*fraction))
		return ;
	ft_memcpy(*fraction, bin->mantissa + 1 + bin->exp,
			(param->length[l_L] ? 63 : 52) - bin->exp);
}

/*
**	"Big" means greater than the number of bits.
*/

static void	case_exp_big
	(char *integer, char **fraction, t_param *param, t_bin *bin)
{
	ft_memcpy(integer, bin->mantissa, (param->length[l_L] ? 64 : 53));
	ft_memset(integer + (param->length[l_L] ? 64 : 53), '0',
			bin->exp - (param->length[l_L] ? 63 : 52));
	*fraction = ft_strnew(1);
	if (!(*fraction))
		return ;
	(*fraction)[0] = '0';
}

char		*get_normal_notation(t_param *param, t_bin *bin)
{
	char *integer;
	char *fraction;
	char *out;

	if (bin->exp == FP_ILOGB0)
		bin->exp = 0;
	if (bin->exp < 0)
		case_exp_negative(&integer, &fraction, param, bin);
	else
	{
		integer = ft_strnew(1 + bin->exp);
		if (!integer)
			return (NULL);
		if (bin->exp < (param->length[l_L] ? 63 : 52))
			case_exp_small(integer, &fraction, param, bin);
		else
			case_exp_big(integer, &fraction, param, bin);
	}
	out = binary_to_decimal(integer, fraction);
	if (integer)
		free(integer);
	if (fraction)
		free(fraction);
	return (out);
}
