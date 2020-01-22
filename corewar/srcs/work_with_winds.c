/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_winds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:19:05 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/18 14:15:59 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_win	*ft_create_windows(void)
{
	t_win *wins;

	wins = (t_win *)malloc(sizeof(t_win));
	if (!wins)
		return (NULL);
	wins->frame = newwin(FRAME_H, FRAME_L, 0, 0);
	wins->battlefield = subwin(wins->frame, BATTLEFIELD_H, BATTLEFIELD_L,
		BATTLEFIELD_Y, BATTLEFIELD_X);
	wins->info = subwin(wins->frame, INFO_H, INFO_L, INFO_Y, INFO_X);
	keypad(wins->frame, TRUE);
	nodelay(wins->frame, TRUE);
	return (wins);
}

void	ft_destroy_windows(t_win *wins)
{
	delwin(wins->battlefield);
	delwin(wins->info);
	delwin(wins->frame);
	endwin();
}

void	ft_key_control(t_vm *vm)
{
	int		button;

	if (!vm->carrs)
		vm->pause = TRUE;
	button = wgetch(vm->wins->frame);
	if (button == 'm' && vm->sp > 1)
		vm->sp /= 2;
	if (button == 'l' && vm->sp < 0x8FFF)
		vm->sp *= 2;
	if (button == 'p')
		vm->pause = !(vm->pause);
	if (button == 'q')
	{
		if (vm->wins)
			ft_destroy_windows(vm->wins);
		free(vm->wins);
		exit(0);
	}
}

void	ft_refresh_windows(t_vm *vm)
{
	ft_key_control(vm);
	ft_print_frame(vm->wins->frame);
	ft_print_info(vm);
	ft_print_battlefield(vm);
	wrefresh(vm->wins->frame);
	usleep(vm->sp);
}

void	ft_init_ncurses(t_vm *vm)
{
	initscr();
	noecho();
	curs_set(FALSE);
	vm->pause = 1;
	if (!(vm->wins = ft_create_windows()) || !has_colors())
	{
		if (vm->wins)
			ft_destroy_windows(vm->wins);
		free(vm->wins);
		exit(0);
	}
	start_color();
	set_color();
	vm->pause = 1;
}
