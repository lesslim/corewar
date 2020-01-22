/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:53:59 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/18 14:32:17 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# include <ncurses.h>
# include <curses.h>
# include <unistd.h>
# include <fcntl.h>
# include <ncurses.h>

# define CORE_WAR 12
# define MAX_PLAYER 4;
# define EL 120
# define BINNAME "Corewar: "

static uint8_t			g_args[4] = {
	0,
	T_REG,
	T_DIR,
	T_IND
};

typedef struct			s_op
{
	char	*name;
	uint8_t	code;
	int		cycles;
	int		args_num;
	int		t_dir_size;
	int		args_types[3];
}						t_op;

static t_op				g_op[17] = {
	{
		.name = "kostyl",
		.code = 0x00,
		.cycles = 0,
		.args_num = 1,
		.t_dir_size = 4,
		.args_types = {T_DIR, 0, 0}
	},
	{
		.name = "live",
		.code = 0x01,
		.cycles = 10,
		.args_num = 1,
		.t_dir_size = 4,
		.args_types = {T_DIR, 0, 0}
	},
	{
		.name = "ld",
		.code = 0x02,
		.cycles = 5,
		.args_num = 2,
		.t_dir_size = 4,
		.args_types = {T_DIR | T_IND, T_REG, 0}
	},
	{
		.name = "st",
		.code = 0x03,
		.cycles = 5,
		.args_num = 2,
		.t_dir_size = 4,
		.args_types = {T_REG, T_REG | T_IND, 0}
	},
	{
		.name = "add",
		.code = 0x04,
		.cycles = 10,
		.args_num = 3,
		.t_dir_size = 4,
		.args_types = {T_REG, T_REG, T_REG}
	},
	{
		.name = "sub",
		.code = 0x05,
		.cycles = 10,
		.args_num = 3,
		.t_dir_size = 4,
		.args_types = {T_REG, T_REG, T_REG}
	},
	{
		.name = "and",
		.code = 0x06,
		.cycles = 6,
		.args_num = 3,
		.t_dir_size = 4,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}
	},
	{
		.name = "or",
		.code = 0x07,
		.cycles = 6,
		.args_num = 3,
		.t_dir_size = 4,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}
	},
	{
		.name = "xor",
		.code = 0x08,
		.cycles = 6,
		.args_num = 3,
		.t_dir_size = 4,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.cycles = 20,
		.args_num = 1,
		.t_dir_size = 2,
		.args_types = {T_DIR, 0, 0}
	},
	{
		.name = "ldi",
		.code = 0x0a,
		.cycles = 25,
		.args_num = 3,
		.t_dir_size = 2,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}
	},
	{
		.name = "sti",
		.code = 0x0b,
		.cycles = 25,
		.args_num = 3,
		.t_dir_size = 2,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR}
	},
	{
		.name = "fork",
		.code = 0x0c,
		.cycles = 800,
		.args_num = 1,
		.t_dir_size = 2,
		.args_types = {T_DIR, 0, 0}
	},
	{
		.name = "lld",
		.code = 0x0d,
		.cycles = 10,
		.args_num = 2,
		.t_dir_size = 4,
		.args_types = {T_DIR | T_IND, T_REG, 0}
	},
	{
		.name = "lldi",
		.code = 0x0e,
		.cycles = 50,
		.args_num = 3,
		.t_dir_size = 2,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}
	},
	{
		.name = "lfork",
		.code = 0x0f,
		.cycles = 1000,
		.args_num = 1,
		.t_dir_size = 2,
		.args_types = {T_DIR, 0, 0}
	},
	{
		.name = "aff",
		.code = 0x10,
		.cycles = 2,
		.args_num = 1,
		.t_dir_size = 4,
		.args_types = {T_REG, 0, 0}
	}
};

typedef struct			s_champ
{
	int				num;
	uint32_t		header;
	char			*name;
	char			*comment;
	int32_t			size;
	char			*code;
	struct s_champ	*next;
	struct s_champ	*prev;
}						t_champ;

typedef struct			s_win
{
	WINDOW			*frame;
	WINDOW			*battlefield;
	WINDOW			*info;
	WINDOW			*headers;
}						t_win;

typedef struct			s_carr
{
	int				id;
	_Bool			carry;
	uint32_t		oper_code;
	int				last_live;
	int				cycles_to_exe;
	int				curr_pos;
	int				step_byte;
	int				reg[REG_NUMBER];
	struct s_carr	*next;
	uint8_t			args_types[3];
	int				args[3];
}						t_carr;

typedef struct			s_vm
{
	int				dmp;
	int				num_pl;
	unsigned char	arena[MEM_SIZE];
	unsigned int	colors[MEM_SIZE];
	t_champ			*players;
	t_win			*wins;
	t_carr			*carrs;
	t_champ			*last_live;
	int				cycle;
	int				live;
	int				cycles_after_check;
	int				cycles_to_die;
	int				num_check;
	int				carr_num;
	int				all_carrs;
	int				pause;
	int				sp;
	_Bool			aff_flag;
	_Bool			vis_flag;
	_Bool			l_flag;
}						t_vm;

int						ft_parse(t_vm *vm, int nbr_param, char **input);
int						read_champion(char *filename, t_champ *champion);
int						champ_order(t_vm *vm);
t_champ					*goto_nchamp(t_vm *vm, int n);
void					champ_sort(t_vm *vm);
void					free_all(t_vm *vm);
void					reverse_bytes(void *data_ptr, size_t size);
int						init_arena(t_vm *vm);
void					print_champ_info(t_vm *vm);
int						put_champ_on_arena(t_vm *vm, int step);
int						init_carr(t_vm *vm);
void					ft_copy_fork(t_carr *car, int new_pos, t_vm *vm);
void					game(t_vm *vm);
int						get_types(t_vm *vm, t_carr *carr, t_op *op);
int						valid_types(t_carr *carr, t_op *op);
void					print_arena(t_vm *vm, unsigned char *arena);
void					check_dead(t_vm *vm);
int						get_args(t_vm *vm, t_carr *carr);
int						shift(t_carr *carr);
void					make_oper(t_vm *vm, t_carr *carr);
void					print_winner(t_vm *vm);
int						ft_where(int pos);
void					these_op(t_vm *vm, t_carr *carr);
void					those_op(t_vm *vm, t_carr *carr);
void					put_value(t_vm *vm, t_carr *carr, int c, int size);
int						make_arg(t_vm *vm, int pos, int size);
int						have_type(t_carr *carr, int *i);
int						get_ind(t_vm *vm, t_carr *carr, int shift, int i);

void					live(t_vm *vm, t_carr *car);
void					and(t_vm *vm, t_carr *carr);
void					or(t_vm *vm, t_carr *carr);
void					xor(t_vm *vm, t_carr *carr);
void					zjmp(t_vm *vm, t_carr *carr);
void					sti(t_vm *vm, t_carr *carr);
void					add(t_carr *carr);
void					sub(t_carr *carr);
void					ld(t_vm *vm, t_carr *carr);
void					lld(t_vm *vm, t_carr *carr);
void					ldi(t_vm *vm, t_carr *carr);
void					lldi(t_vm *vm, t_carr *carr);
void					ft_fork(t_vm *vm, t_carr *carr);
void					lfork(t_vm *vm, t_carr *carr);
void					aff(t_vm *vm, t_carr *carr);
void					st(t_vm *vm, t_carr *carr);
int						val(t_vm *vm, char **input, int index);

attr_t					ft_get_color(t_vm *vm, int pos);
void					ft_print_frame(WINDOW *frame);
void					ft_print_picture(WINDOW *win,\
char *picture, int str_count);
void					ft_print_info(t_vm *vm);
void					ft_print_battlefield(t_vm *vm);
t_win					*ft_create_windows(void);
void					ft_destroy_windows(t_win *wins);
void					ft_key_control(t_vm *vm);
void					ft_refresh_windows(t_vm *vm);
void					ft_init_ncurses(t_vm *vm);
void					ft_init_pairs(void);
t_carr					*find_carr(t_vm *vm, int i);
int						carr_is_here(t_vm *vm, int pos);
void					set_color(void);
char					*ft_sizedup(const char *s, size_t n);

#endif
