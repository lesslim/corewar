/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:57:54 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:24:17 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <unistd.h>

void	print_arena(t_vm *vm, unsigned char *arena)
{
	int	i;
	int	j;
	int k;

	i = 0;
	k = 32;
	if (vm->l_flag)
		k = 64;
	while (i < MEM_SIZE)
	{
		ft_printf("0x%.4x : ", i);
		j = 0;
		while (j < k)
		{
			ft_printf("%.2x ", (int)arena[i + j]);
			j++;
		}
		ft_printf("\n");
		i += k;
	}
}

int		put_champ_on_arena(t_vm *vm, int step)
{
	int		i;
	int		j;
	t_champ *champ;

	i = 0;
	champ = vm->players;
	while (champ)
	{
		j = 0;
		while (i < MEM_SIZE - 1 && j < champ->size)
		{
			vm->arena[i++] = champ->code[j++];
			vm->colors[i] = champ->num;
		}
		while (i % step != 0)
			i++;
		champ = champ->next;
	}
	return (0);
}

void	set_arena_col(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->colors[i] = 0;
		i++;
	}
}

int		init_arena(t_vm *vm)
{
	set_arena_col(vm);
	put_champ_on_arena(vm, MEM_SIZE / vm->num_pl);
	return (1);
}
