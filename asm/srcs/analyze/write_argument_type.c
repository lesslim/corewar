/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_argument_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:34:07 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "g_op.h"

static size_t	get_arg_size(unsigned int arg_code, uint8_t op_code)
{
	if (arg_code == DIR_CODE)
		return (g_op[op_code].t_dir_2o ? IND_SIZE : DIR_SIZE);
	else
		return (arg_code == IND_CODE ? IND_SIZE : REG_NUMBER_SIZE);
}

int				write_argument_type(t_instruction *instr, t_list *token_lst)
{
	t_token			*token;
	unsigned int	code;
	unsigned int	arg_id;

	token = token_lst->content;
	if (token->type == rx_arg_dir || token->type == rx_arg_l_dir)
		code = DIR_CODE;
	else if (token->type == rx_arg_ind || token->type == rx_arg_l_ind)
		code = IND_CODE;
	else
		code = REG_CODE;
	if (!(instr->coding_byte & ARG1))
		arg_id = 1;
	else if (!(instr->coding_byte & ARG2))
		arg_id = 2;
	else if (!(instr->coding_byte & ARG3))
		arg_id = 3;
	else
		return (token_error(MSG_TOO_MANY_ARGS, token_lst));
	instr->coding_byte |= code << ((4u - arg_id) * 2u);
	token->bin_size = get_arg_size(code, instr->code);
	instr->arg_sizes[arg_id - 1] = token->bin_size;
	return (0);
}
