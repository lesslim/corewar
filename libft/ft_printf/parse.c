/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:44 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:00:36 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "parse_helpers.h"
#include "handle_helpers.h"

static void	initialize_param(t_param *param)
{
	ft_bzero(param->flags, N_FLAGS);
	param->width = -1;
	param->precision = -1;
	ft_bzero(param->length, N_LENGTH);
	param->type = -1;
	ft_bzero(param->pre, PREPEND_LENGTH);
}

static void	parse_special_types(t_param *param)
{
	if (param->type == t_i)
		param->type = t_d;
	else if (param->type > INTEGERS_SP_START && param->type < INTEGERS_SP_END)
	{
		if (!param->length[1])
			++(param->length[1]);
		param->type = ft_strfind(TYPES, ft_tolower(TYPES[param->type]));
	}
	else if (param->type == t_p)
	{
		param->flags[f_hash] = 1;
		param->length[l_l] = 1;
	}
	else if (param->type == t_C || param->type == t_S)
	{
		--(param->type);
		param->length[l_l] = 1;
	}
}

static void	set_default_precision(t_param *param)
{
	if (param->precision < 0 && (param->type == t_f || param->type == t_F
			|| param->type == t_e || param->type == t_E
			|| param->type == t_g || param->type == t_G))
		param->precision = 6;
}

static int	h_n(t_param *param, va_list args, int counter)
{
	void	*addr;
	int		size;

	size = choose_size(param);
	if (size == INT && (addr = va_arg(args, int *)))
		*((int *)addr) = counter;
	else if (size == LONG && (addr = va_arg(args, long *)))
		*((long *)addr) = counter;
	else if (size == LLONG && (addr = va_arg(args, long long *)))
		*((long long *)addr) = counter;
	else if (size == INTMAX && (addr = va_arg(args, intmax_t *)))
		*((intmax_t *)addr) = counter;
	else if (size == PTRDIFF && (addr = va_arg(args, ptrdiff_t *)))
		*((ptrdiff_t *)addr) = counter;
	return (0);
}

int			parse(const char **s, va_list args, int counter)
{
	t_param param;

	initialize_param(&param);
	++(*s);
	while (**s && ft_strfind(ALLOWED_SYMBOLS, **s) > -1)
	{
		parse_flags(s, &param);
		parse_width(s, &param, args);
		parse_precision(s, &param, args);
		parse_length(s, &param);
		parse_type(s, &param);
		if (param.type != NO_TYPE)
			break ;
	}
	if (param.type == NO_TYPE)
	{
		--(param.width);
		if (!(**s))
			return (0);
	}
	parse_special_types(&param);
	set_default_precision(&param);
	if (param.type == t_n)
		return (h_n(&param, args, counter));
	return (handle(&param, args));
}
