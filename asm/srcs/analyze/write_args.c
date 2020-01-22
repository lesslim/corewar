/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:33:49 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "g_op.h"

static void	write_clipped_arg(int64_t raw_value, unsigned int arg_id,
		t_instruction *instr, uint8_t arg_type)
{
	uint8_t		size;

	if (arg_type == rx_arg_l_dir || arg_type == rx_arg_dir)
		size = g_op[instr->code].t_dir_2o ? IND_SIZE : DIR_SIZE;
	else
		size = (arg_type == rx_arg_reg) ? REG_NUMBER_SIZE : IND_SIZE;
	if (size == 1)
		instr->args[arg_id].byte1 = (int8_t)raw_value;
	else if (size == 2)
		instr->args[arg_id].byte2 = (int16_t)raw_value;
	else
		instr->args[arg_id].byte4 = (int32_t)raw_value;
}

static int	check_range(int64_t raw, t_list *current_token)
{
	t_token	*arg;

	arg = current_token->content;
	if (arg->type == rx_arg_reg && (raw < 1 || raw > REG_NUMBER))
		return (token_error(MSG_INVAL_REGNO, current_token));
	return (0);
}

static int	write_arg(t_instruction *instr, unsigned int *counter,
		t_htab *labels, t_list *current_token)
{
	t_token	*arg;
	int64_t	raw;
	int64_t	hash;

	arg = current_token->content;
	errno = 0;
	if (arg->type == rx_arg_l_ind || arg->type == rx_arg_l_dir)
	{
		if ((hash = ft_htgetid(labels,
				arg->text + (arg->type == rx_arg_l_dir) + 1,
				ft_strlen(arg->text + (arg->type == rx_arg_l_dir) + 1))) == -1)
			return (token_error(MSG_UNKNOWN_LAB, current_token));
		raw = (int32_t)*(unsigned int *)labels->items[hash]->value
				+ instr->op_size - (int32_t)counter[0];
	}
	else
		raw = ft_ltoi_safe(arg->text + (arg->type != rx_arg_ind));
	write_clipped_arg(raw, counter[1], instr, arg->type);
	if (errno || (arg->bin_size == 1 && instr->args[counter[1]].byte1 != raw)
		|| (arg->bin_size == 2 && instr->args[counter[1]].byte2 != raw)
		|| (arg->bin_size == 4 && instr->args[counter[1]].byte4 != raw))
		token_error(MSG_OVERUNDERFLOW, current_token);
	counter[1]++;
	return (check_range(raw, current_token));
}

/*
**	unsigned int	counter[2] = {current_addr, arg_id};
*/

int			write_args(t_list *current_token, t_htab *labels)
{
	t_instruction	*current_op;
	unsigned int	counter[2];

	ft_bzero(counter, sizeof(counter));
	current_op = NULL;
	while (current_token)
	{
		if (((t_token *)current_token->content)->type == rx_op)
		{
			counter[0] += ((t_token *)current_token->content)->bin_size;
			current_op = ((t_token *)current_token->content)->bin;
			current_op->op_size = ((t_token *)current_token->content)->bin_size;
			counter[1] = 0;
		}
		else if (is_argument(current_token->content)
				&& write_arg(current_op, counter, labels, current_token) == -1)
			return (-1);
		current_token = current_token->next;
	}
	return (0);
}
