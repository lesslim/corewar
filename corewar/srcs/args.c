/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:48:22 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:25:55 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		make_arg(t_vm *vm, int stand, int size)
{
	int				i;
	unsigned int	arr[size];
	unsigned int	tmp;
	int				j;
	int				test;

	test = 0;
	j = 0;
	i = -1;
	tmp = 0;
	while (++i < size)
		arr[i] = vm->arena[ft_where(stand + i)];
	while (--i >= 0)
	{
		test = arr[j];
		if (vm->arena[stand] & 0x80)
			test = (test ^ 0xFF) << (i * 8);
		else
			test = test << (i * 8);
		tmp += test;
		j++;
	}
	return (vm->arena[stand] & 0x80 ? ~(tmp) : tmp);
}

int		get_args(t_vm *vm, t_carr *carr)
{
	int i;
	int shift;

	shift = have_type(carr, &i);
	while (++i < g_op[carr->oper_code].args_num)
	{
		if (carr->args_types[i] == T_REG && ++shift)
		{
			carr->args[i] = make_arg(vm, ft_where(carr->curr_pos +
			shift - 1), 1);
			if (carr->args[i] > REG_NUMBER || carr->args[i] < 1)
				return (0);
		}
		else if (carr->args_types[i] == T_DIR)
		{
			carr->args[i] = make_arg(vm, ft_where(carr->curr_pos + shift),
			g_op[carr->oper_code].t_dir_size);
			shift += g_op[carr->oper_code].t_dir_size;
		}
		else if (carr->args_types[i] == T_IND)
			shift += get_ind(vm, carr, shift, i);
	}
	return (1);
}

int		valid_types(t_carr *carr, t_op *op)
{
	if (!(carr->args_types[0] & op->args_types[0])
	|| (!(carr->args_types[1] & op->args_types[1]) && op->args_num > 1)
	|| (!(carr->args_types[2] & op->args_types[2]) && op->args_num > 2))
	{
		return (0);
	}
	return (1);
}

int8_t	where_it(t_vm *vm, t_carr *carr, int step)
{
	return (vm->arena[(carr->curr_pos + step) % MEM_SIZE]);
}

int		get_types(t_vm *vm, t_carr *carr, t_op *op)
{
	int8_t	byte;

	if (op->args_num > 1 || carr->oper_code == 0x10)
	{
		byte = where_it(vm, carr, 1);
		carr->args_types[0] = g_args[(byte >> 6) & 0x03];
		carr->args_types[1] = g_args[(byte >> 4) & 0x03];
		carr->args_types[2] = g_args[(byte >> 2) & 0x03];
		if (!carr->args_types[0] || (!carr->args_types[1] && op->args_num > 1)
		|| (!carr->args_types[2] && op->args_num > 2))
			return (0);
	}
	else
	{
		carr->args_types[0] = op->args_types[0];
		carr->args_types[1] = 0;
		carr->args_types[2] = 0;
	}
	return (1);
}
