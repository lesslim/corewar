/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:58:22 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/06 21:04:40 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	nbrs_init(int *nbrs, int n)
{
	int i;

	i = -1;
	while (++i <= n)
		nbrs[i] = 0;
}

int		get_numbers(t_vm *vm, int *nbrs)
{
	t_champ *tmp;

	tmp = vm->players;
	while (tmp)
	{
		if (tmp->num > 0)
		{
			if (tmp->num > vm->num_pl || nbrs[tmp->num] > 0)
				return (0);
			else
				nbrs[tmp->num] = 1;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		set_numbers(t_vm *vm, int *nbrs)
{
	t_champ *tmp;
	int		i;

	tmp = vm->players;
	i = 1;
	while (tmp)
	{
		if (tmp->num == 0)
		{
			while (nbrs[i] > 0)
				i++;
			nbrs[i] = 1;
			tmp->num = i;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		champ_order(t_vm *vm)
{
	int nbrs[vm->num_pl + 1];

	nbrs_init(nbrs, vm->num_pl + 1);
	if (!get_numbers(vm, nbrs) || !set_numbers(vm, nbrs))
		return (1);
	return (0);
}
