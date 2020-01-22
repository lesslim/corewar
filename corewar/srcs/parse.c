/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:12:29 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:26:58 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		champ_value(t_champ *champ, t_champ *prev, int num, char *name)
{
	if (prev != NULL)
		prev->next = champ;
	champ->prev = prev;
	champ->next = NULL;
	champ->num = num;
	if (!read_champion(name, champ))
		return (0);
	return (1);
}

int		champ_init(t_vm *vm, int num, char *name)
{
	t_champ *tmp;
	t_champ *tmp2;

	if (vm->players)
	{
		tmp = vm->players;
		tmp2 = vm->players;
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		if (!(tmp = (t_champ*)malloc(sizeof(t_champ))))
			return (0);
		if (!champ_value(tmp, tmp2, num, name))
			return (0);
	}
	else
	{
		if (!(vm->players = (t_champ*)malloc(sizeof(t_champ))) ||
			!champ_value(vm->players, NULL, num, name))
			return (0);
	}
	vm->num_pl += 1;
	return (1);
}

int		is_dotcor(t_vm *vm, char **input, int index, int id)
{
	int len;

	len = ft_strlen(input[index]);
	if (len < 5 || !ft_strequ(input[index] + len - 4, ".cor"))
		return (MEM_SIZE);
	if (!champ_init(vm, id, input[index]))
		return (MEM_SIZE);
	return (1);
}

int		parse_flag(t_vm *vm, char **input, int index, int num)
{
	if (ft_strequ(input[index], "-n"))
	{
		if (num > index + 2 && ft_atoi(input[index + 1]) > 0)
		{
			return (is_dotcor(vm, input, index + 2,
							ft_atoi(input[index + 1])) + 2);
		}
	}
	else if (ft_strequ(input[index], "-dump"))
	{
		if (num > index + 1 && ft_atoi(input[index + 1]) >= 0 && vm->dmp == -1)
		{
			vm->dmp = ft_atoi(input[index + 1]);
			return (2);
		}
	}
	else
	{
		if (val(vm, input, index))
			return (1);
	}
	return (num + 1);
}

int		ft_parse(t_vm *vm, int num_param, char **input)
{
	int i;

	i = 1;
	while (i < num_param)
	{
		if (input[i][0] == '-')
			i += parse_flag(vm, input, i, num_param);
		else
			i += is_dotcor(vm, input, i, 0);
	}
	if (i > num_param || vm->num_pl > MAX_PLAYERS || vm->num_pl == 0)
		return (1);
	if (vm->vis_flag)
	{
		vm->dmp = -1;
		vm->aff_flag = 0;
	}
	return (0);
}
