/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:30:06 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/07 17:46:06 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	these_op(t_vm *vm, t_carr *carr)
{
	if (carr->oper_code == 0x01)
		live(vm, carr);
	if (carr->oper_code == 0x02)
		ld(vm, carr);
	if (carr->oper_code == 0x03)
		st(vm, carr);
	if (carr->oper_code == 0x04)
		add(carr);
	if (carr->oper_code == 0x05)
		sub(carr);
	if (carr->oper_code == 0x06)
		and(vm, carr);
	if (carr->oper_code == 0x07)
		or(vm, carr);
	if (carr->oper_code == 0x08)
		xor(vm, carr);
}

void	those_op(t_vm *vm, t_carr *carr)
{
	if (carr->oper_code == 0x09)
		zjmp(vm, carr);
	if (carr->oper_code == 0x0a)
		ldi(vm, carr);
	if (carr->oper_code == 0x0b)
		sti(vm, carr);
	if (carr->oper_code == 0x0c)
		ft_fork(vm, carr);
	if (carr->oper_code == 0x0d)
		lld(vm, carr);
	if (carr->oper_code == 0x0e)
		lldi(vm, carr);
	if (carr->oper_code == 0x0f)
		lfork(vm, carr);
	if (carr->oper_code == 0x10)
		aff(vm, carr);
}

void	aff(t_vm *vm, t_carr *carr)
{
	if (vm->aff_flag)
		ft_printf("Aff: %c\n", carr->reg[carr->args[0] - 1]);
}

int		get_ind(t_vm *vm, t_carr *carr, int shift, int i)
{
	carr->args[i] = make_arg(vm, ft_where(carr->curr_pos + shift), IND_SIZE);
	return (IND_SIZE);
}

t_champ	*goto_nchamp(t_vm *vm, int n)
{
	int		i;
	t_champ *tmp;

	i = 0;
	tmp = vm->players;
	while (++i < n)
		tmp = tmp->next;
	return (tmp);
}
