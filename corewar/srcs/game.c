/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:42:22 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:22:46 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	put_op(t_vm *vm, t_carr *carr)
{
	carr->oper_code = vm->arena[carr->curr_pos];
	if (carr->oper_code >= 0x01 && carr->oper_code <= 0x10)
		carr->cycles_to_exe = g_op[carr->oper_code].cycles;
}

void	op_exe(t_vm *vm, t_carr *carr)
{
	t_op *op;

	op = NULL;
	if (carr->oper_code >= 0x01 && carr->oper_code <= 0x10)
	{
		op = &g_op[carr->oper_code];
		if (!get_types(vm, carr, op) || !valid_types(carr, op) ||
		!get_args(vm, carr))
			carr->curr_pos = ft_where(carr->curr_pos + shift(carr));
		else
		{
			make_oper(vm, carr);
			if (carr->oper_code != 0x09 ||
			(carr->oper_code == 0x09 && !(carr->carry)))
				carr->curr_pos = ft_where(carr->curr_pos + shift(carr));
		}
	}
	else
		carr->curr_pos = ft_where(carr->curr_pos + 1);
}

void	make_op(t_vm *vm, t_carr *carr)
{
	if (!(carr->cycles_to_exe))
		put_op(vm, carr);
	if (carr->cycles_to_exe > 0)
		--(carr->cycles_to_exe);
	if (!(carr->cycles_to_exe))
		op_exe(vm, carr);
}

void	make_cycle(t_vm *vm)
{
	t_carr *tmp;

	++(vm->cycle);
	++(vm->cycles_after_check);
	tmp = vm->carrs;
	while (tmp)
	{
		make_op(vm, tmp);
		tmp = tmp->next;
	}
}

void	game(t_vm *vm)
{
	while (vm->carr_num)
	{
		if (!(vm->pause))
		{
			if (vm->cycle == vm->dmp)
			{
				print_arena(vm, vm->arena);
				exit(0);
			}
			make_cycle(vm);
			if (vm->cycles_after_check == vm->cycles_to_die ||
			vm->cycles_to_die <= 0)
				check_dead(vm);
		}
		if (vm->vis_flag)
			ft_refresh_windows(vm);
	}
}
