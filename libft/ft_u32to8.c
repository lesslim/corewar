/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u32to8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:25:54 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:25:55 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_u32to8(wchar_t in, char *out)
{
	int				len;
	int				i;

	if (in < 0x80)
		len = 1;
	else if (in < 0x800)
		len = 2;
	else if (in < 0x10000)
		len = 3;
	else
		len = 4;
	out[0] = 0b11110000 << (4 - len + (len == 1));
	i = len;
	while (i > 1)
	{
		out[i - 1] = 0b10000000 ^ (0b00111111 & in);
		in = in >> 6;
		i--;
	}
	out[0] = out[0] ^ ((0b11111111 >> (len + 1 - (len == 1))) & in);
	return (len);
}
