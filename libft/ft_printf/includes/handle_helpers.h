/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_helpers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:05:58 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:05:59 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_HELPERS_H
# define HANDLE_HELPERS_H

# include "bases.h"

# define D(x) ((x) - '0')

char		*h_s(t_param *param, va_list args);
char		*h_c(t_param *param, va_list args);

char		*h_signed(t_param *param, va_list args);
char		*h_unsigned(t_param *param, va_list args);
char		*h_double(t_param *param, va_list args);

enum e_size choose_size(t_param *param);
int			find_insignificant_zeros(char *s);
void		remove_trailing_zeros(char *s);
int			get_base(t_param *param);
void		signed_prepend(int negative, t_param *param);

char		*get_mantissa16(t_param *param, t_bin *bin);
char		*get_mantissa10(t_param *param, t_bin *bin, int *exp);

char		*get_normal_notation(t_param *param, t_bin *bin);

void		handle_decimal_precision(char *s, t_param *param);

size_t		get_length_w_precision(char *s, int precision);
void		h_g_normal_notation_post(t_param *param, char *normal_notation);

#endif
