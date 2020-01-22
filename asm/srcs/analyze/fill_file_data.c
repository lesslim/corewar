/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:33:27 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_n_labels(t_list *tokens)
{
	int	n_labels;

	if (!tokens)
		return (ft_msg(MSG_GNL_ERROR, NULL, -1, STDERR_FILENO));
	n_labels = 0;
	while (tokens)
	{
		n_labels += ((t_token *)tokens->content)->type == rx_label;
		tokens = tokens->next;
	}
	return (n_labels);
}

static int	add_label(t_htab *labels, unsigned int current_addr,
		t_list *token_lst)
{
	t_token		*token;
	t_hash_item	*hitem;
	size_t		len;

	token = token_lst->content;
	len = ft_strlen(token->text) - 1;
	if (ft_htgetid(labels, token->text, len) != -1)
		return (token_error(MSG_DUPLICATE, token_lst));
	if (!(hitem = ft_hinew(token->text, len,
			&current_addr, sizeof(unsigned int))))
		return (ft_msg(strerror(ENOMEM), NULL, -1, STDERR_FILENO));
	ft_htadd(labels, hitem);
	return (0);
}

static int	write_name_comment(t_file *file, t_list *current_tok)
{
	if (((t_token *)current_tok->content)->type == rx_champ_name)
	{
		if (file->name)
			return (token_error(MSG_DUPLICATE_NAME, current_tok));
		file->name = current_tok;
	}
	else if (((t_token *)current_tok->content)->type == rx_champ_comment)
	{
		if (file->comment)
			return (token_error(MSG_DUPLICATE_CMNT, current_tok));
		file->comment = current_tok;
	}
	return (0);
}

/*
**	Writes name, comment, size, labels
*/

int			fill_file_data(t_file *file, t_htab **labels)
{
	unsigned int	current_addr;
	t_list			*current_tok;

	if (!(*labels = ft_htnew(ft_nextprime(get_n_labels(file->tokens)),
			BASE_ASCII, ALTBASE_ASCII)))
		return (ft_msg(strerror(ENOMEM), NULL, -1, STDERR_FILENO));
	current_addr = 0;
	current_tok = file->tokens;
	while (current_tok)
	{
		if (write_name_comment(file, current_tok) == -1)
			return (-1);
		else if (((t_token *)current_tok->content)->type == rx_op)
			current_addr += ((t_token *)current_tok->content)->bin_size;
		else if (((t_token *)current_tok->content)->type == rx_label
				&& add_label(*labels, current_addr, current_tok) == -1)
		{
			ft_htdel(labels, ft_hidel);
			return (-1);
		}
		current_tok = current_tok->next;
	}
	file->size = current_addr;
	return (0);
}
