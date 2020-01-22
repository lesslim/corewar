/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:32:43 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 15:32:43 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int		ft_printf(const char *s, ...)
{
	va_list	args;
	int		counter;
	int		n_printed;

	va_start(args, s);
	counter = 0;
	while (*s)
	{
		if (*s != '%')
		{
			n_printed = ft_pututf_fd(s, 1);
			s += n_printed;
			counter += n_printed;
		}
		else
			counter += parse(&s, args, counter);
	}
	va_end(args);
	return (counter);
}
