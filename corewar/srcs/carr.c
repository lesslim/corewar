/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:50:52 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/06 20:50:59 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	put_carr(t_vm *vm, t_carr *carry, t_champ *champ)
{
	int j;

	carry->id = champ->num;
	carry->cycles_to_exe = 0;
	carry->curr_pos = ((MEM_SIZE / vm->num_pl) * (carry->id - 1));
	carry->reg[0] = -(carry->id);
	carry->next = NULL;
	j = 0;
	while (++j < REG_NUMBER)
		carry->reg[j] = 0;
}

int		init_carr(t_vm *vm)
{
	t_carr	*carry;
	t_carr	*tmp;
	t_champ	*tmpch;

	tmp = NULL;
	tmpch = vm->players;
	vm->carr_num = vm->num_pl;
	vm->all_carrs = vm->num_pl;
	while (tmpch)
	{
		if (!(carry = (t_carr*)ft_memalloc(sizeof(t_carr))))
			return (0);
		put_carr(vm, carry, tmpch);
		carry->next = tmp;
		tmp = carry;
		carry = carry->next;
		tmpch = tmpch->next;
	}
	vm->carrs = tmp;
	vm->last_live = goto_nchamp(vm, vm->num_pl);
	return (1);
}
