/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:53:26 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/06 20:34:42 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_player(t_vm *vm)
{
	t_champ *tmp;
	t_champ *tmp2;

	tmp = vm->players;
	tmp2 = vm->players;
	while (tmp)
	{
		tmp = tmp->next;
		if (tmp2->name)
			free(tmp2->name);
		if (tmp2->comment)
			free(tmp2->comment);
		if (tmp2->code)
			free(tmp2->code);
		free(tmp2);
		tmp2 = tmp;
	}
}

void	free_carr(t_vm *vm)
{
	t_carr *tmpc1;
	t_carr *tmpc2;

	tmpc1 = vm->carrs;
	tmpc2 = vm->carrs;
	while (tmpc1)
	{
		tmpc1 = tmpc1->next;
		free(tmpc2);
		tmpc2 = tmpc1;
	}
}

void	free_all(t_vm *vm)
{
	free_player(vm);
	free_carr(vm);
	if (vm->wins)
		free(vm->wins);
	if (vm)
		free(vm);
}
