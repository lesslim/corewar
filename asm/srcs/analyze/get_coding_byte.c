/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coding_byte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:30 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "g_op.h"

unsigned int	get_n_args(t_instruction *instr)
{
	unsigned int	n_args;

	n_args = 0;
	n_args += (instr->coding_byte & ARG1) != 0;
	n_args += (instr->coding_byte & ARG2) != 0;
	n_args += (instr->coding_byte & ARG3) != 0;
	return (n_args);
}

static int		unexpected_args(unsigned int arg_id, t_list *instr_token_lst)
{
	ft_putstr_fd(ASM_NAME": ", STDERR_FILENO);
	ft_putstr_fd(MSG_CAC_ARG_ID, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd(arg_id + 1 + '0', STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (token_error(MSG_UNEXPECTED_ARG, instr_token_lst));
}

static int		check_args_consistency(t_instruction *instr,
		t_list *instr_token_lst)
{
	unsigned int	n_args;
	unsigned int	i;
	unsigned int	code;

	if ((n_args = get_n_args(instr)) != g_op[instr->code].n_args)
		return (token_error(MSG_INVAL_ARGNO, instr_token_lst));
	i = 0;
	while (i < n_args)
	{
		code = ((0b11000000u >> i * 2) & instr->coding_byte) >> 2 * (3 - i);
		if ((code == REG_CODE && !g_op[instr->code].arg_types[i].t_reg)
			|| (code == DIR_CODE && !g_op[instr->code].arg_types[i].t_dir)
			|| (code == IND_CODE && !g_op[instr->code].arg_types[i].t_ind))
			return (unexpected_args(i, instr_token_lst));
		++i;
	}
	return (0);
}

int				get_coding_byte(t_list **token_lst, t_instruction *instr,
		t_list *instr_token_lst)
{
	t_list	*current;

	if (!(current = *token_lst))
		return (ft_msg(MSG_UNEXPECTED_EOF, NULL, -1, STDERR_FILENO));
	while (is_argument(current->content))
	{
		if (write_argument_type(instr, current) == -1)
			return (-1);
		if (!(current = current->next))
			return (ft_msg(MSG_UNEXPECTED_EOF, NULL, -1, STDERR_FILENO));
		if (((t_token *)current->content)->type == rx_arg_sep)
			if (!(current = current->next))
				return (ft_msg(MSG_UNEXPECTED_EOF, NULL, -1, STDERR_FILENO));
	}
	if (((t_token *)current->content)->type != rx_ws_mf)
		return (token_error(MSG_UNEXPECTED_TOK, current));
	*token_lst = current->next;
	return (check_args_consistency(instr, instr_token_lst));
}
