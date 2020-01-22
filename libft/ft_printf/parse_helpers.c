/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:44 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:01:21 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "parse_helpers.h"

void	parse_flags(const char **s, t_param *param)
{
	int id;

	while (**s && (id = ft_strfind(FLAGS, **s)) > -1)
	{
		param->flags[id] = 1;
		++(*s);
	}
}

void	parse_width(const char **s, t_param *param, va_list args)
{
	int	out;

	if (**s == '*')
	{
		param->width = va_arg(args, int);
		if (param->width < 0)
		{
			param->flags[f_minus] = 1;
			param->width *= -1;
		}
		++(*s);
		return ;
	}
	if (!ft_isdigit(**s))
		return ;
	out = 0;
	while (ft_isdigit(**s))
	{
		out *= 10;
		out += **s - '0';
		++(*s);
	}
	param->width = out;
}

void	parse_precision(const char **s, t_param *param, va_list args)
{
	int out;

	if (**s != '.')
		return ;
	++(*s);
	if (**s == '*')
	{
		param->precision = va_arg(args, int);
		++(*s);
		return ;
	}
	out = 0;
	while (ft_isdigit(**s))
	{
		out *= 10;
		out += **s - '0';
		++(*s);
	}
	param->precision = out;
}

void	parse_length(const char **s, t_param *param)
{
	int	id;

	while (**s && (id = ft_strfind(LENGTH, **s)) > -1)
	{
		if (**s == 'l')
			param->length[id] += param->length[id] < 3 ? 1 : 0;
		else if (**s == 'h')
			++(param->length[id]);
		else
			param->length[id] = 1;
		++(*s);
	}
}

void	parse_type(const char **s, t_param *param)
{
	int idx;

	if (!(**s))
		return ;
	idx = ft_strfind(TYPES, **s);
	if (idx < 0)
		return ;
	++(*s);
	param->type = idx;
}
