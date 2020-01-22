/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_decimal_precision.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:59:16 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

static void	up_one(char *s, int i, t_param *param)
{
	while (--i >= 0)
	{
		if (s[i] == '.')
			continue ;
		if (s[i] - '0' < 9)
		{
			++(s[i]);
			return ;
		}
		else
			s[i] = '0';
	}
	if (i == -1)
		ft_strcat(param->pre, "1");
}

/*
**	Getting to the first char after the dot in the first loop;
**	Then proceeding to the char that needs to be evaluated to determine
**	which way to round.
**  Rounding up if the digit is greater than five or if there are non-zero
**  digits after the one in question or if the digit is equal to five and the
**  preceding digit is odd.
*/

void		handle_decimal_precision(char *s, t_param *param)
{
	int	i;
	int	j;
	int prev;

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
	prev = (s[i + j - 1] != '.') ? (i + j - 1) : (i + j - 2);
	if (D(s[i + j]) > 5 || (D(s[i + j]) == 5
			&& (ft_strfindnot(s + i + j + 1, '0') != -1 || s[prev] % 2)))
		up_one(s, i + j, param);
	s[i + j] = '\0';
}
