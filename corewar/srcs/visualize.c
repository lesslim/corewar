/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:27:11 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/18 14:31:55 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	g_core_war[CORE_WAR][100] =
{
	" ####  ###  ####  #####     \n",
	"#     #   # #   # #         \n",
	"#     #   # ####  #####     \n",
	"#     #   # #  #  #         \n",
	" ####  ###  #   # #####     \n",
	"                            \n",
	" #           #  #   #### \n",
	"  #         #  # #  #   #\n",
	"   #   #   #  ##### #### \n",
	"    # # # #   #   # #  # \n",
	"     #   #    #   # #   #\n"
};

void	ft_print_name(t_champ *player, WINDOW *win)
{
	char	*tmp;

	if (ft_strlen(player->name) <= 19)
		wprintw(win, "%d - %s\n", player->num, player->name);
	else
	{
		tmp = ft_sizedup(player->name, 19);
		wprintw(win, "%d - %s...\n", player->num, tmp);
		free(tmp);
	}
	if (ft_strlen(player->comment) <= 19)
		wprintw(win, "%s\n", player->comment);
	else
	{
		tmp = ft_sizedup(player->comment, 19);
		wprintw(win, "%s...\n", tmp);
		free(tmp);
	}
}

void	ft_players_inf(t_vm *vm, WINDOW *win)
{
	int		i;
	t_champ	*player;

	i = 1;
	while (i <= MAX_PLAYERS && vm->players)
	{
		wattron(win, COLOR_PAIR(i));
		if ((player = vm->players))
		{
			ft_print_name(player, win);
			wattron(win, COLOR_PAIR(MAX_PLAYERS + 11));
		}
		wattroff(win, COLOR_PAIR(i));
		vm->players = vm->players->next;
		i++;
	}
}

void	ft_printing(t_vm *vm, WINDOW *win)
{
	char	*tmp;

	wmove(win, 0, 0);
	wattron(win, COLOR_PAIR(MAX_PLAYERS + 4));
	ft_print_picture(win, g_core_war[0], CORE_WAR);
	wprintw(win, "Total cycle: %d\n", vm->cycle);
	wprintw(win, "Cycle after check: %d\n", vm->cycles_after_check);
	wprintw(win, "Cycle to die: %d\n", vm->cycles_to_die);
	wprintw(win, "Speed: %f\n", 1000.0 / vm->sp);
	tmp = ft_sizedup(vm->last_live->name, 19);
	wprintw(win, "Count of carrs: %d\nWinner: %s",\
	vm->carr_num, tmp);
	free(tmp);
}

void	ft_print_info(t_vm *vm)
{
	WINDOW	*win;
	t_champ	*tmp;
	t_carr	*tmp_carrs;

	win = vm->wins->info;
	tmp_carrs = vm->carrs;
	tmp = vm->players;
	if (vm->carr_num)
	{
		ft_printing(vm, win);
		wprintw(win, "\nChampions:\n");
		tmp = vm->players;
		ft_players_inf(vm, win);
	}
	else
	{
		wattron(win, COLOR_PAIR(vm->last_live->num));
		wprintw(win, "%d, \"%s\", has won !\n",
		vm->last_live->num, vm->last_live->name);
	}
	vm->players = tmp;
}

void	ft_print_battlefield(t_vm *vm)
{
	WINDOW	*win;
	attr_t	attrs;
	int		i;

	win = vm->wins->battlefield;
	wmove(win, 0, 0);
	i = 0;
	while (i < MEM_SIZE)
	{
		attrs = ft_get_color(vm, i);
		wattron(win, attrs);
		wprintw(win, "%02hhx", vm->arena[i]);
		wattroff(win, attrs);
		wprintw(win, " ");
		i++;
	}
}
