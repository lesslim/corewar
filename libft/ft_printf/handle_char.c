/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:58:15 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

static int	check_char(char *c, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!(*(c + i)))
			return (0);
		++i;
	}
	return (1);
}

static void	remove_trailing_broken_characters(char *s)
{
	int char_len;

	while (*s)
	{
		char_len = ft_uchar_len(s);
		if (!check_char(s, char_len))
		{
			*s = '\0';
			return ;
		}
		s += char_len;
	}
}

char		*h_s(t_param *param, va_list args)
{
	char	*out;

	if (param->length[l_l])
		out = ft_wstrdup(va_arg(args, wchar_t *));
	else
		out = ft_strdup(va_arg(args, char *));
	if (!out)
		out = ft_strdup("(null)");
	if (!out)
		return (NULL);
	if (param->precision >= 0 && param->precision < (int)ft_strlen(out))
	{
		out[param->precision] = '\0';
		if (param->length[l_l])
			remove_trailing_broken_characters(out);
	}
	return (out);
}

char		*h_c(t_param *param, va_list args)
{
	char	*out;

	out = ft_memalloc(4);
	if (param->length[l_l])
		ft_u32to8((wchar_t)va_arg(args, wint_t), out);
	else
		out[0] = (unsigned char)(va_arg(args, int));
	return (out);
}
