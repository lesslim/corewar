/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:41:58 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:27:52 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	and(t_vm *vm, t_carr *carr)
{
	int a;
	int b;

	if (carr->args_types[0] == T_REG)
		a = carr->reg[carr->args[0] - 1];
	else if (carr->args_types[0] == T_DIR)
		a = carr->args[0];
	else
		a = make_arg(vm, ft_where(carr->curr_pos +
		(carr->args[0] % IDX_MOD)), 4);
	if (carr->args_types[1] == T_REG)
		b = carr->reg[carr->args[1] - 1];
	else if (carr->args_types[1] == T_DIR)
		b = carr->args[1];
	else
		b = make_arg(vm, ft_where(carr->curr_pos +
		(carr->args[1] % IDX_MOD)), 4);
	carr->reg[carr->args[2] - 1] = a & b;
	if (carr->reg[carr->args[2] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}

void	or(t_vm *vm, t_carr *carr)
{
	int a;
	int b;

	if (carr->args_types[0] == T_REG)
		a = carr->reg[carr->args[0] - 1];
	else if (carr->args_types[0] == T_DIR)
		a = carr->args[0];
	else
		a = make_arg(vm, ft_where(carr->curr_pos +
		(carr->args[0] % IDX_MOD)), 4);
	if (carr->args_types[1] == T_REG)
		b = carr->reg[carr->args[1] - 1];
	else if (carr->args_types[1] == T_DIR)
		b = carr->args[1];
	else
		b = make_arg(vm, ft_where(carr->curr_pos +
		(carr->args[1] % IDX_MOD)), 4);
	carr->reg[carr->args[2] - 1] = a | b;
	if (carr->reg[carr->args[2] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}

void	xor(t_vm *vm, t_carr *carr)
{
	int a;
	int b;

	if (carr->args_types[0] == T_REG)
		a = carr->reg[carr->args[0] - 1];
	else if (carr->args_types[0] == T_DIR)
		a = carr->args[0];
	else
		a = make_arg(vm, ft_where(carr->curr_pos +
		(carr->args[0] % IDX_MOD)), 4);
	if (carr->args_types[1] == T_REG)
		b = carr->reg[carr->args[1] - 1];
	else if (carr->args_types[1] == T_DIR)
		b = carr->args[1];
	else
		b = make_arg(vm, ft_where(carr->curr_pos +
		(carr->args[1] % IDX_MOD)), 4);
	carr->reg[carr->args[2] - 1] = a ^ b;
	if (carr->reg[carr->args[2] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}

void	zjmp(t_vm *vm, t_carr *carr)
{
	if (vm)
	{
		if (carr->carry)
		{
			carr->curr_pos = ft_where(carr->curr_pos +
			((carr->args[0]) % IDX_MOD));
		}
	}
}

void	ldi(t_vm *vm, t_carr *carr)
{
	int a;
	int b;

	if (carr->args_types[0] == T_REG)
		a = carr->reg[carr->args[0] - 1];
	else if (carr->args_types[0] == T_DIR)
		a = carr->args[0];
	else
		a = make_arg(vm, ft_where(carr->curr_pos +
		(carr->args[0] % IDX_MOD)), 4);
	if (carr->args_types[1] == T_REG)
		b = carr->reg[carr->args[1] - 1];
	else
		b = carr->args[1];
	carr->reg[carr->args[2] - 1] = make_arg(vm,
	ft_where(carr->curr_pos + ((a + b) % IDX_MOD)), 4);
}
