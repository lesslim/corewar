/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:25:37 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:33:36 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

long	ft_ltoi_safe(const char *str)
{
	long	out;
	long	temp;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = (*str != '-') - (*str == '-');
	str += (*str == '-' || *str == '+');
	out = 0;
	while (ft_isdigit(*str))
	{
		temp = out;
		out *= 10;
		if (out / 10 != temp)
			errno = ERANGE;
		out += (*str - '0') * sign;
		str++;
		if ((sign < 0 && temp < out) || (sign > 0 && temp > out))
			errno = ERANGE;
	}
	return (out);
}
