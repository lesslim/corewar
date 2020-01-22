/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command10.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:43:20 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:29:20 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sti(t_vm *vm, t_carr *carr)
{
	int a;
	int b;
	int c;

	if (carr->args_types[2] == T_REG)
		a = carr->reg[carr->args[2] - 1];
	else
		a = carr->args[2];
	if (carr->args_types[1] == T_REG)
		b = carr->reg[carr->args[1] - 1];
	else if (carr->args_types[1] == T_DIR)
		b = carr->args[1];
	else
		b = make_arg(vm, ft_where(carr->curr_pos + (carr->args[1] %
		IDX_MOD)), 4);
	c = ft_where(carr->curr_pos + ((a + b) % IDX_MOD));
	put_value(vm, carr, c, 4);
}

void	ft_fork(t_vm *vm, t_carr *carr)
{
	t_carr	*new;
	int		i;

	if (!(new = (t_carr*)ft_memalloc(sizeof(t_carr))))
		exit(0);
	i = -1;
	while (++i < REG_NUMBER)
		new->reg[i] = carr->reg[i];
	new->carry = carr->carry;
	new->last_live = carr->last_live;
	new->curr_pos = ft_where(carr->curr_pos + (carr->args[0] %
	IDX_MOD));
	new->cycles_to_exe = 0;
	++(vm->all_carrs);
	new->id = vm->all_carrs;
	++(vm->carr_num);
	new->next = vm->carrs;
	vm->carrs = new;
	new->oper_code = 0;
}

void	lld(t_vm *vm, t_carr *carr)
{
	if (carr->args_types[0] == T_DIR)
		carr->reg[carr->args[1] - 1] = carr->args[0];
	else
		carr->reg[carr->args[1] - 1] =
		make_arg(vm, ft_where(carr->curr_pos + carr->args[0]), 2);
	if (carr->reg[carr->args[1] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}

void	lldi(t_vm *vm, t_carr *carr)
{
	int a;
	int b;

	if (carr->args_types[0] == T_REG)
		a = carr->reg[carr->args[0] - 1];
	else if (carr->args_types[0] == T_DIR)
		a = carr->args[0];
	else
		a = make_arg(vm, ft_where(carr->curr_pos + (carr->args[0] %
		IDX_MOD)), 4);
	if (carr->args_types[1] == T_REG)
		b = carr->reg[carr->args[1] - 1];
	else
		b = carr->args[1];
	carr->reg[carr->args[2] - 1] = make_arg(vm,
	ft_where(carr->curr_pos + a + b), 4);
	if (carr->reg[carr->args[2] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
}

void	lfork(t_vm *vm, t_carr *carr)
{
	t_carr	*new;
	int		i;

	if (!(new = (t_carr*)ft_memalloc(sizeof(t_carr))))
		exit(0);
	i = -1;
	while (++i < REG_NUMBER)
		new->reg[i] = carr->reg[i];
	new->carry = carr->carry;
	new->last_live = carr->last_live;
	new->curr_pos = ft_where(carr->curr_pos + carr->args[0]);
	new->cycles_to_exe = 0;
	++(vm->all_carrs);
	new->id = vm->all_carrs;
	++(vm->carr_num);
	new->next = vm->carrs;
	vm->carrs = new;
	new->oper_code = 0;
}
