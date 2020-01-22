/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbig.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:06:16 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:06:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBIG_H
# define LIBBIG_H

# include "libft.h"

# define EON 127

typedef char	* t_big;

enum			e_free
{
	F_NONE,
	F_LEFT,
	F_RIGHT,
	F_ALL
};

int				get_num_len_base(intmax_t n, int base);

t_big			big_add(t_big a, t_big b);
t_big			bigbinup(char *bin);
t_big			big_concat(t_big a, t_big b);
t_big			big_iadd(t_big a, intmax_t b);
t_big			big_iconcat(t_big a, intmax_t b, enum e_free clean);
t_big			big_imult(t_big a, intmax_t b, enum e_free clean);
size_t			big_len(t_big a);
t_big			bigllup(intmax_t x);
t_big			big_mult(t_big a, t_big b);
t_big			bignew(size_t len);
char			*bigtoa(t_big x, enum e_free clean);

#endif
