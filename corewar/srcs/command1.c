/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:38:10 by pdiedra           #+#    #+#             */
/*   Updated: 2019/12/09 22:22:56 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live(t_vm *vm, t_carr *carr)
{
	carr->args[0] *= -1;
	if (carr->args[0] > 0 && carr->args[0] <= vm->num_pl)
		vm->last_live = goto_nchamp(vm, carr->args[0]);
	carr->last_live = vm->cycle;
	++(vm->live);
}

void	ld(t_vm *vm, t_carr *carr)
{
	if (carr->args_types[0] == T_DIR)
		carr->reg[carr->args[1] - 1] = carr->args[0];
	else
		carr->reg[carr->args[1] - 1] =
		make_arg(vm, ft_where(carr->curr_pos + (carr->args[0] % IDX_MOD)), 4);
	if (carr->reg[carr->args[1] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}

void	st(t_vm *vm, t_carr *carr)
{
	if (carr->args_types[1] == T_REG)
		carr->reg[carr->args[1] - 1] = carr->reg[carr->args[0] - 1];
	else
		put_value(vm, carr, ft_where(carr->curr_pos +
		(carr->args[1] % IDX_MOD)), 4);
}

void	add(t_carr *carr)
{
	carr->reg[carr->args[2] - 1] = carr->reg[carr->args[0] - 1] +
	carr->reg[carr->args[1] - 1];
	if (carr->reg[carr->args[2] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}

void	sub(t_carr *carr)
{
	carr->reg[carr->args[2] - 1] = carr->reg[carr->args[0] - 1] -
	carr->reg[carr->args[1] - 1];
	if (carr->reg[carr->args[2] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}
