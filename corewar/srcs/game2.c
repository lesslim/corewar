/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:59:27 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/07 13:15:04 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		shift(t_carr *carr)
{
	int sh;
	int i;

	sh = 1;
	if (carr->oper_code == 0x10 || g_op[carr->oper_code].args_num > 1)
		++sh;
	i = -1;
	while (++i < g_op[carr->oper_code].args_num)
	{
		if (carr->args_types[i] == T_REG)
			sh += REG_LEN;
		else if (carr->args_types[i] == T_IND)
			sh += IND_SIZE;
		else if (carr->args_types[i] == T_DIR)
			sh += g_op[carr->oper_code].t_dir_size;
	}
	return (sh);
}

int		ft_where(int pos)
{
	pos %= MEM_SIZE;
	if (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}

int		have_type(t_carr *carr, int *i)
{
	*i = -1;
	if (carr->oper_code != 0x01 && carr->oper_code != 0x09 &&
	carr->oper_code != 0x0c && carr->oper_code != 0x0f)
		return (2);
	return (1);
}

void	put_value(t_vm *vm, t_carr *carr, int c, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		vm->arena[(c + size - 1 - i) % MEM_SIZE] =
		(carr->reg[carr->args[0] - 1] >> (i * 8)) & 255;
		vm->colors[(c + size - 1 - i) % MEM_SIZE] = carr->id;
	}
}

void	make_oper(t_vm *vm, t_carr *carr)
{
	if (carr->oper_code < 9)
		these_op(vm, carr);
	if (carr->oper_code > 8)
		those_op(vm, carr);
}
