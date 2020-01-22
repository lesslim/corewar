/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:32:47 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "g_op.h"

static int		get_code(t_list **token_lst, t_token *token)
{
	int				code;
	t_instruction	*instr;

	instr = token->bin;
	code = 1;
	while (code <= TOTAL_OPS)
	{
		if (ft_strequ(token->text, g_op[code].op_name))
		{
			instr->code = code;
			if (!(*token_lst = (*token_lst)->next))
				return (ft_msg(MSG_UNEXPECTED_EOF, NULL, -1, STDERR_FILENO));
			return (0);
		}
		++code;
	}
	return (token_error(MSG_UNKNOWN_OP, *token_lst));
}

static int		get_instruction_size(t_token *token)
{
	t_instruction	*instr;
	unsigned int	i;
	unsigned int	code;

	instr = token->bin;
	token->bin_size = 1 + g_op[instr->code].coding_arg_type;
	i = 0;
	while (i < 3)
	{
		code = ((0b11000000u >> i * 2) & instr->coding_byte) >> 2 * (3 - i);
		if (!code)
			break ;
		if (code == DIR_CODE)
			token->bin_size += g_op[instr->code].t_dir_2o ? IND_SIZE : DIR_SIZE;
		else
			token->bin_size += (code == IND_CODE ? IND_SIZE : REG_NUMBER_SIZE);
		++i;
	}
	return (0);
}

int				analyzer_op(t_list **token_lst)
{
	t_token *token;
	t_list	*instr_token_lst;

	instr_token_lst = *token_lst;
	token = (*token_lst)->content;
	if (!(token->bin = ft_memalloc(sizeof(t_instruction))))
		return (ft_msg(strerror(ENOMEM), NULL, -1, STDERR_FILENO));
	if (get_code(token_lst, token) == -1
		|| get_coding_byte(token_lst, token->bin, instr_token_lst) == -1
		|| get_instruction_size(token) == -1)
		return (-1);
	return (0);
}
