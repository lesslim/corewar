/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_name_and_comment.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:30 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_name_comment_size(t_token *token)
{
	if (token->type == rx_champ_name && token->bin_size > PROG_NAME_LENGTH)
		return (ft_msg(MSG_NAME_TOO_LONG, NULL, -1, STDERR_FILENO));
	if (token->type == rx_champ_comment && token->bin_size > COMMENT_LENGTH)
		return (ft_msg(MSG_CMNT_TOO_LONG, NULL, -1, STDERR_FILENO));
	return (0);
}

int			analyzer_name_and_comment(t_list **token_lst)
{
	t_token			*token;

	if (!token_lst || !(*token_lst) || !(*token_lst)->content)
		return (ft_msg(MSG_ANC_ERROR, NULL, -1, STDERR_FILENO));
	token = (*token_lst)->content;
	token->bin = ft_strchr(token->text, '"') + 1;
	token->bin_size = ft_strchr(token->bin, '"') - (char *)token->bin;
	if (!token->bin_size)
		return (token_error(MSG_EMPTY_NC, *token_lst));
	*token_lst = (*token_lst)->next;
	return (check_name_comment_size(token));
}
