/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_op.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:18 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:31:13 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "g_op.h"

/*
**	Consider updating regex_op.h if you make changes below
*/

const t_op	g_op[TOTAL_OPS + 1] =
{
	{"", 0, 0, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}},
	{"live", 1, 0, 0, {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}}},
	{"ld", 2, 1, 0, {{0, 1, 1}, {1, 0, 0}, {0, 0, 0}}},
	{"st", 2, 1, 0, {{1, 0, 0}, {1, 0, 1}, {0, 0, 0}}},
	{"add", 3, 1, 0, {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}},
	{"sub", 3, 1, 0, {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}},
	{"and", 3, 1, 0, {{1, 1, 1}, {1, 1, 1}, {1, 0, 0}}},
	{"or", 3, 1, 0, {{1, 1, 1}, {1, 1, 1}, {1, 0, 0}}},
	{"xor", 3, 1, 0, {{1, 1, 1}, {1, 1, 1}, {1, 0, 0}}},
	{"zjmp", 1, 0, 1, {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}}},
	{"ldi", 3, 1, 1, {{1, 1, 1}, {1, 1, 0}, {1, 0, 0}}},
	{"sti", 3, 1, 1, {{1, 0, 0}, {1, 1, 1}, {1, 1, 0}}},
	{"fork", 1, 0, 1, {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}}},
	{"lld", 2, 1, 0, {{0, 1, 1}, {1, 0, 0}, {0, 0, 0}}},
	{"lldi", 3, 1, 1, {{1, 1, 1}, {1, 1, 0}, {1, 0, 0}}},
	{"lfork", 1, 0, 1, {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}}},
	{"aff", 1, 1, 0, {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}}
};