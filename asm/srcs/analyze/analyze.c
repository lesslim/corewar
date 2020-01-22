/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:37:29 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "g_op.h"

static int	skip(t_list **token)
{
	if (!token)
		return (ft_msg(MSG_CA_RAISE, NULL, -1, STDERR_FILENO));
	*token = (*token)->next;
	return (0);
}

static int	raise(t_list **token)
{
	if (token)
		return (token_error(MSG_UNEXPECTED_TOK, *token));
	else
		return (ft_msg("raise: Argument token is NULL",
				NULL, -1, STDERR_FILENO));
}

static int	(*choose_analyzer(t_token *token))(t_list **token)
{
	if ((token->type >= rx_skippable && token->type < rx_champ_name)
			|| token->type == rx_label)
		return (skip);
	if (token->type == rx_champ_name || token->type == rx_champ_comment)
		return (analyzer_name_and_comment);
	if (token->type == rx_op)
		return (analyzer_op);
	return (raise);
}

static int	exit_analyze(char *msg, t_htab **labels, int exit_code)
{
	if (labels)
		ft_htdel(labels, ft_hidel);
	if (!msg)
		return (exit_code);
	return (ft_msg(msg, NULL, exit_code, STDERR_FILENO));
}

int			analyze(t_file *file)
{
	t_list	*token;
	t_htab	*labels;

	token = file->tokens;
	while (token)
		if (choose_analyzer(token->content)(&token) == -1)
			return (-1);
	labels = NULL;
	if (fill_file_data(file, &labels) == -1)
		return (exit_analyze(NULL, &labels, -1));
	if (!labels)
		return (exit_analyze(NULL, &labels, -1));
	if (!file->name)
		return (exit_analyze(MSG_NO_NAME, &labels, -1));
	if (!file->comment)
		return (exit_analyze(MSG_NO_COMMENT, &labels, -1));
	if (!file->size)
		return (exit_analyze(MSG_NO_INSTR, &labels, -1));
	if (write_args(file->tokens, labels) == -1)
		return (exit_analyze(NULL, &labels, -1));
	return (exit_analyze(NULL, &labels, 0));
}
