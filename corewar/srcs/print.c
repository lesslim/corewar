/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:57:20 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:19:44 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_champ_info(t_vm *vm)
{
	t_champ *tmp;

	tmp = vm->players;
	ft_putstr("Introducing contestants...\n");
	while (tmp)
	{
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
				tmp->num, tmp->size, tmp->name, tmp->comment);
		tmp = tmp->next;
	}
}

void	print_winner(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
	vm->last_live->num, vm->last_live->name);
}

void	reverse_bytes(void *data_ptr, size_t size)
{
	size_t	i;
	uint8_t	*data;
	uint8_t	temp;

	if (!data_ptr | !size)
		return ;
	data = data_ptr;
	i = 0;
	while (i < size / 2)
	{
		temp = data[i];
		data[i] = data[size - 1 - i];
		data[size - 1 - i] = temp;
		++i;
	}
}

int		val(t_vm *vm, char **input, int index)
{
	if (ft_strequ(input[index], "-a") && !vm->aff_flag)
	{
		++(vm->aff_flag);
		return (1);
	}
	if (ft_strequ(input[index], "-v") && !vm->vis_flag)
	{
		++(vm->vis_flag);
		return (1);
	}
	if (ft_strequ(input[index], "-l") && !vm->l_flag)
	{
		++(vm->l_flag);
		return (1);
	}
	return (0);
}
