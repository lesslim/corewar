/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_regexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:27 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:27 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	compile_regexes(t_fa_state **regexes)
{
	int	i;

	i = 0;
	while (i < rx_total_number)
	{
		regexes[i] = ft_regex_compile(RX_PATTERS[i]);
		if (!regexes[i])
		{
			del_regexes(regexes, i);
			return (-1);
		}
		++i;
	}
	return (0);
}
