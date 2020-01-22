/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:36:11 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/18 14:32:03 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->dmp = -1;
	vm->cycles_to_die = CYCLE_TO_DIE;
	return (0);
}

void	graphic(t_vm *vm)
{
	if (vm->vis_flag)
	{
		ft_init_ncurses(vm);
		vm->sp = DELAY;
	}
	else
	{
		vm->pause = 0;
		print_champ_info(vm);
	}
}

void	print_help(void)
{
	ft_putstr("\nUsage: corewar file0.cor file1.cor\
	... fileN.cor flags\n");
	ft_putstr("about flags:\n");
	ft_putstr("-v 			for visualisation\n");
	ft_putstr("-a 			for aff (outputs nothing by default)\n");
	ft_putstr("[-dump nbr_cycles] 	after nbr_cycles print arena\
	(32 octets per line by default)\n");
	ft_putstr("-l 			for 64 octets per line in dump\n");
	ft_putstr("[[-n number] 		champion.cor]\
	sets the number of the next player\n");
}

int		main(int ac, char **av)
{
	t_vm *vm;

	if (!(vm = (t_vm*)malloc(sizeof(t_vm))) || vm_init(vm))
	{
		ft_putstr_fd("We have no memory :(\n", STDERR_FILENO);
		exit(1);
	}
	if (ac < 2 || ft_parse(vm, ac, av) || champ_order(vm))
	{
		ft_putstr(BINNAME"Invalid input\n");
		print_help();
		exit(1);
	}
	champ_sort(vm);
	if (!init_arena(vm))
		return (2);
	init_carr(vm);
	graphic(vm);
	game(vm);
	if (!vm->vis_flag)
		print_winner(vm);
	free_all(vm);
	return (0);
}
