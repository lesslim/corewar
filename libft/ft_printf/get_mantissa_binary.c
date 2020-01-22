/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mantissa_binary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:47:04 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "bases.h"

char	*get_mantissa_binary(double x, int exp)
{
	char	*out;
	char	temp[64];
	void	*addr;
	int		i;

	addr = &x;
	out = ft_strnew(52 + 1);
	if (!out)
		return (NULL);
	out[0] = (exp == FP_ILOGB0) ? '0' : '1';
	out[52 + 1] = '\0';
	i = 0;
	while (i < 64)
	{
		temp[8 * (7 - i / 8) + i % 8] = (*((unsigned char *)addr + i / 8)
											& (0x80 >> i % 8)) ? '1' : '0';
		++i;
	}
	ft_memcpy(out + 1, temp + 12, 52);
	return (out);
}

char	*get_mantissa_binary_long(long double x)
{
	char	*out;
	char	temp[80];
	void	*addr;
	int		i;

	addr = &x;
	out = ft_strnew(64);
	if (!out)
		return (NULL);
	out[64] = '\0';
	i = 0;
	while (i < 80)
	{
		temp[8 * (9 - i / 8) + i % 8] = (*((unsigned char *)addr + i / 8)
										& (0x80 >> i % 8)) ? '1' : '0';
		++i;
	}
	ft_memcpy(out, temp + 16, 64);
	return (out);
}
