/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_gf_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:32:43 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

size_t	get_length_w_precision(char *s, int precision)
{
	int		dot_i;
	size_t	len;
	size_t	frlen;
	size_t	intlen;

	len = ft_strlen(s);
	if (precision <= 0)
		return (len);
	dot_i = ft_strfind(s, '.');
	frlen = len - 1 - dot_i;
	intlen = len - frlen;
	return (intlen + (((ssize_t)frlen > precision) ? frlen : precision));
}

void	h_g_normal_notation_post(t_param *param, char *normal_notation)
{
	long	i;

	if ((i = ft_strfind(normal_notation, '.')) == -1)
		return ;
	if (!param->flags[f_hash])
		remove_trailing_zeros(normal_notation);
	if (!normal_notation[i + 1] && !param->flags[f_hash])
		normal_notation[i] = '\0';
}
