/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:21:48 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/18 14:15:40 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		carr_is_here(t_vm *vm, int pos)
{
	t_carr	*tmp;
	int		res;

	tmp = vm->carrs;
	while (vm->carrs)
	{
		if (vm->arena[pos] == vm->carrs->curr_pos)
		{
			res = vm->carrs->id;
			vm->carrs = tmp;
			return (res);
		}
		vm->carrs = vm->carrs->next;
	}
	vm->carrs = tmp;
	return (-1);
}

t_carr	*find_carr(t_vm *vm, int i)
{
	t_carr	*res;

	res = vm->carrs;
	while (res)
	{
		if (res->id == i)
			return (res);
		if (res->next)
			res = res->next;
		else
			return (NULL);
	}
	return (NULL);
}

void	ft_init_pairs(void)
{
	init_pair(MAX_PLAYERS + 1, COLOR_BLACK, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 2, COLOR_RED, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 3, COLOR_GREEN, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 5, COLOR_BLACK, COLOR_RED);
	init_pair(MAX_PLAYERS + 6, COLOR_BLACK, COLOR_YELLOW);
	init_pair(MAX_PLAYERS + 7, COLOR_BLACK, COLOR_GREEN);
	init_pair(MAX_PLAYERS + 8, COLOR_BLACK, COLOR_CYAN);
	init_pair(MAX_PLAYERS + 9, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(MAX_PLAYERS + 10, COLOR_BLACK, COLOR_BLUE);
	init_pair(MAX_PLAYERS + 11, COLOR_RED, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 12, COLOR_YELLOW, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 13, COLOR_GREEN, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 14, COLOR_CYAN, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 15, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(MAX_PLAYERS + 16, COLOR_BLUE, COLOR_BLACK);
}

char	*ft_sizedup(const char *s, size_t n)
{
	unsigned int	i;
	char			*res;

	if ((res = (char*)malloc(sizeof(*res) * (n + 1))))
	{
		i = -1;
		while (*s && ++i < n)
			res[i] = s[i];
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
