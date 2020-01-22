/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:03:15 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/07/02 16:04:52 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include "ft_printf.h"

# include <math.h>
# include <wchar.h>

# include "libft.h"

# include <limits.h>
# include <stddef.h>
# include <sys/types.h>

enum			e_signals
{
	s_error = -127,
	s_ntype,
	s_lntype
};

# define ALLOWED_SYMBOLS "-+ 0#123456789.hlLzjtdiouxXDOUeEfFgGaA%cCsSpn*"
# define BASE "0123456789abcdef"

# define N_FLAGS 5
# define FLAGS "-+ 0#"

enum			e_flags
{
	f_minus,
	f_plus,
	f_space,
	f_zero,
	f_hash
};

# define N_LENGTH 6
# define LENGTH "hlLzjt"

enum			e_length
{
	l_h,
	l_l,
	l_L,
	l_z,
	l_j,
	l_t
};

enum			e_size
{
	INT,
	LONG,
	LLONG,
	SIZE_T,
	INTMAX,
	PTRDIFF
};

# define TYPES "doupxXiDOUefgaEFGA%cCsSn"

/*
**	The structure of TYPES is as follows:
**		Integer types
**			regular integer types (douxX)
**			special integer types (iDOU)
**		Double types (eEfFgGaA)
**		Char types (%cC)
**		String types (sS)
**		Special types (pn)
*/

enum			e_types
{
	NO_TYPE = -1,
	t_d, t_o, t_u, t_p, t_x, t_X,
	t_i, t_D, t_O, t_U,
	t_e, t_f, t_g, t_a, t_E, t_F, t_G, t_A,
	t_prcnt, t_c, t_C,
	t_s, t_S,
	t_n,
	INTEGERS_REG_START = t_d, INTEGERS_REG_END = t_i,
	INTEGERS_SP_START = t_i, INTEGERS_SP_END = t_e,
	DOUBLES_START = t_e, DOUBLES_CAPITAL_START = t_E, DOUBLES_END = t_prcnt
};

/*
**	To choose a type, go
** 		either for direct comparison: if (foo == t_bar)
** 		or for ranges [)
** 		or for ranges () to exclude the first character (somewhat special, too)
*/

# define PREPEND_LENGTH 3

typedef struct	s_param
{
	char			flags[N_FLAGS];
	int				width;
	int				precision;
	char			length[N_LENGTH];
	enum e_types	type;
	char			pre[PREPEND_LENGTH];
}				t_param;

int				parse(const char **s, va_list args, int counter);
int				handle(t_param *param, va_list args);
int				output(char *s, t_param *param);

#endif
