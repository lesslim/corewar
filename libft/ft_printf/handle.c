/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:57:56 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "handle_helpers.h"

int	handle(t_param *param, va_list args)
{
	char	*out;

	if (param->type == t_s)
		out = h_s(param, args);
	else if (param->type == t_c)
		out = h_c(param, args);
	else if (param->type == t_prcnt)
		out = ft_strdup("%");
	else if (param->type == t_d)
		out = h_signed(param, args);
	else if (param->type > INTEGERS_REG_START && param->type < INTEGERS_SP_END)
		out = h_unsigned(param, args);
	else if (param->type >= DOUBLES_START && param->type < DOUBLES_END)
		out = h_double(param, args);
	else
		out = ft_strnew(0);
	if (!out)
		out = ft_strdup("(null)");
	return (output(out, param));
}

int	output(char *s, t_param *param)
{
	int	len;
	int	left;
	int	ignore_f_zero;

	ignore_f_zero = (param->type >= INTEGERS_REG_START
					&& param->type < INTEGERS_SP_END
					&& param->precision >= 0);
	len = ft_strlen(s) + ft_strlen(param->pre) + (!(*s) && param->type == t_c);
	left = param->flags[f_minus] == 1;
	if (param->flags[3] && !ignore_f_zero)
		ft_putstr_utf_fd(param->pre, 1);
	if (!left && param->width > len)
		ft_putnchar((param->flags[f_zero] && !ignore_f_zero) ? '0' : ' ',
					param->width - len);
	if (!param->flags[f_zero] || ignore_f_zero)
		ft_putstr(param->pre);
	if (param->type == t_c)
		ft_pututf_fd_safe(s, 1);
	else
		ft_putstr_utf_fd_safe(s, 1);
	if (left && param->width > len)
		ft_putnchar(' ', param->width - len);
	free(s);
	return (param->width > len ? param->width : len);
}
