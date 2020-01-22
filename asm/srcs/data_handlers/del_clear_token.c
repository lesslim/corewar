/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_clear_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:27 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:27 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	champ_name and champ_comment just keep references to text
*/

void	clear_token(t_token *token)
{
	if (token->text)
	{
		free(token->text);
		token->text = NULL;
	}
	if (token->bin
			&& token->type != rx_champ_name
			&& token->type != rx_champ_comment)
	{
		free(token->bin);
		token->bin = NULL;
	}
}

void	del_token(void **content, size_t *size)
{
	if (!content || !(*content))
		return ;
	clear_token(*content);
	free(*content);
	*content = NULL;
	if (size)
		*size = 0;
}
