/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:07:24 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:07:43 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASES_H
# define BASES_H

typedef struct	s_binary
{
	char	*mantissa;
	int		exp;
}				t_bin;

enum			e_binary_padding
{
	PAD_RIGHT,
	PAD_LEFT
};

char			*binary_to_decimal
		(char *integer, char *fraction);
char			*binary_fraction_to_decimal(char *bin);
char			*bin2hex(char *binary, int padding);

int				get_num_len_base(intmax_t n, int base);

void			read_double_as_binary(t_param *param, va_list args, t_bin *bin);
char			*get_mantissa_binary(double x, int exp);
char			*get_mantissa_binary_long(long double x);

#endif
