/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:24:39 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/18 14:15:18 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	set_color(void)
{
	int i;
	int color;

	ft_init_pairs();
	i = 1;
	while (i <= MAX_PLAYERS)
	{
		color = 7 - (COLOR_BLACK + i - 1) % 7;
		init_pair(i, color, COLOR_BLACK);
		i++;
	}
}

attr_t	ft_choose_col(t_vm *vm, int pos, attr_t attrs)
{
	int		i;

	i = carr_is_here(vm, pos);
	if (i == -1)
	{
		if (vm->colors[pos] <= MAX_PLAYERS)
			attrs = COLOR_PAIR(vm->colors[pos]);
		else
		{
			i = MAX_PLAYERS + 11 + vm->colors[pos] % 6;
			attrs = COLOR_PAIR(i);
		}
	}
	else
	{
		if (carr_is_here(vm, pos) <= MAX_PLAYERS)
			attrs = COLOR_PAIR(carr_is_here(vm, pos)) | A_REVERSE;
		else
		{
			i = MAX_PLAYERS + 5 + carr_is_here(vm, pos) % 6;
			attrs = COLOR_PAIR(i);
		}
	}
	return (attrs);
}

attr_t	ft_get_color(t_vm *vm, int pos)
{
	attr_t	attrs;

	attrs = COLOR_PAIR(MAX_PLAYERS + 1) | A_BOLD;
	if (vm->arena[pos])
		attrs = COLOR_PAIR(vm->arena[pos]);
	if (vm->arena[pos])
		attrs = ft_choose_col(vm, pos, attrs);
	else if (vm->arena[pos])
	{
		vm->arena[pos]--;
		attrs = attrs | A_BOLD;
	}
	return (attrs);
}

void	ft_print_frame(WINDOW *frame)
{
	int i;
	int j;
	int color;

	color = MAX_PLAYERS + 1;
	i = 0;
	while (i < FRAME_H)
	{
		j = 0;
		while (j < FRAME_L)
		{
			if ((j < 1 && i < 1) || (i == FRAME_H - 1 && j == FRAME_L - 1) ||
			(i == FRAME_H - 1 && j < 1) || (i < 1 && j == FRAME_L - 1))
				mvwaddch(frame, i, j, 'O' | COLOR_PAIR(color));
			else if (i < 1 || i == FRAME_H - 1)
				mvwaddch(frame, i, j, '#' | COLOR_PAIR(color) | A_BOLD);
			else if (j < 1 || j >= FRAME_L - 1 || j == INFO_X - 4)
				mvwaddch(frame, i, j, '#' | COLOR_PAIR(color) | A_BOLD);
			j++;
		}
		i++;
	}
}

void	ft_print_picture(WINDOW *win, char *picture, int str_count)
{
	char	*str;
	int		i;

	i = 0;
	wprintw(win, "\n");
	while (i < str_count)
	{
		str = picture + i * 100;
		wprintw(win, "%s", str);
		i++;
	}
	wprintw(win, "\n");
}
