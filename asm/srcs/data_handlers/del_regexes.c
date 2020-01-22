/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_regexes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:27 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:38:10 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_regexes(t_fa_state **regexes, int n_regexes)
{
	int	i;

	i = -1;
	while (++i < n_regexes)
		ft_regex_del(regexes + i);
}
