/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:41:10 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/07 13:50:42 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champ	*find_nchamp(t_vm *vm, int n)
{
	t_champ *tmp;

	tmp = vm->players;
	while (tmp->num != n)
		tmp = tmp->next;
	return (tmp);
}

void	fix_neib(t_champ *left, t_champ *right, t_champ *new)
{
	if (left)
		left->next = new;
	if (right)
		right->prev = new;
}

void	fix_champ(t_champ *left, t_champ *right, t_champ *champ)
{
	champ->prev = left;
	champ->next = right;
}

void	champ_swap(t_champ *wrong, t_champ *right)
{
	t_champ *tmp;
	t_champ *tmp2;

	if (wrong->next != right)
	{
		fix_neib(right->prev, right->next, wrong);
		fix_neib(wrong->prev, wrong->next, right);
		tmp = wrong->prev;
		tmp2 = wrong->next;
		fix_champ(right->prev, right->next, wrong);
		fix_champ(tmp, tmp2, right);
	}
	else
	{
		if (wrong->prev)
			(wrong->prev)->next = right;
		if (right->next)
			(right->next)->prev = wrong;
		tmp = wrong->prev;
		wrong->prev = right;
		wrong->next = right->next;
		right->prev = tmp;
		right->next = wrong;
	}
}

void	champ_sort(t_vm *vm)
{
	int		i;
	t_champ *tmp;

	i = 1;
	tmp = find_nchamp(vm, i);
	if (goto_nchamp(vm, i) != find_nchamp(vm, i))
	{
		champ_swap(goto_nchamp(vm, i), find_nchamp(vm, i));
		vm->players = tmp;
	}
	while (++i <= vm->num_pl)
	{
		if (goto_nchamp(vm, i) != find_nchamp(vm, i))
			champ_swap(goto_nchamp(vm, i), find_nchamp(vm, i));
	}
}
