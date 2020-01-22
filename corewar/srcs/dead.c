/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:09:05 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/06 20:53:50 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	move_on(t_carr **prev, t_carr **curr)
{
	*prev = (*curr);
	(*curr) = (*curr)->next;
}

void		del_dead(t_vm *vm)
{
	t_carr *prev;
	t_carr *curr;
	t_carr *tmp;

	prev = NULL;
	curr = vm->carrs;
	while (curr)
	{
		if (vm->cycles_to_die <= 0 ||
			vm->cycle - curr->last_live >= vm->cycles_to_die)
		{
			if (vm->carrs == curr)
				vm->carrs = curr->next;
			if (prev)
				prev->next = curr->next;
			tmp = curr;
			curr = curr->next;
			free(tmp);
			--(vm->carr_num);
		}
		else
			move_on(&prev, &curr);
	}
}

void		check_dead(t_vm *vm)
{
	++(vm->num_check);
	vm->cycles_after_check = 0;
	del_dead(vm);
	if (vm->num_check == MAX_CHECKS || vm->live >= NBR_LIVE)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->num_check = 0;
	}
	vm->live = 0;
}
