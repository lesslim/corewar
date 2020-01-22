/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:21 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:39:25 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Writes msg, followed by arg, to fd. Returns code.
*/

long		ft_msg(char *msg, char *arg, int code, int fd)
{
	if (!msg)
	{
		ft_putendl_fd("ft_msg: Missing msg", STDERR_FILENO);
		return (-1);
	}
	ft_putstr_fd(ASM_NAME": ", fd);
	if (arg)
	{
		ft_putstr_fd(arg, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putendl_fd(msg, fd);
	return (code);
}

static int	init_token_error(t_list **tokens, char *msg, t_list *token_to_find)
{
	if (msg)
		return (1);
	*tokens = token_to_find;
	return (0);
}

/*
**	Keeps the current list of tokens as a static variable.
**	To reset the list, an empty message should be passed.
**	Then tokens is set to be token_to_find.
*/

int			token_error(char *msg, t_list *token_to_find)
{
	static t_list	*tokens;
	unsigned int	line;

	if (!init_token_error(&tokens, msg, token_to_find))
		return (0);
	line = 1;
	while (tokens && tokens != token_to_find)
	{
		if (((t_token *)tokens->content)->type == rx_ws_mf
				|| ((t_token *)tokens->content)->type == rx_champ_name
				|| ((t_token *)tokens->content)->type == rx_champ_comment)
			line += ft_strcount(((t_token *)tokens->content)->text, '\n');
		tokens = tokens->next;
	}
	ft_putstr_fd(ASM_NAME": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	if (token_to_find && ((t_token *)token_to_find->content)->text)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(((t_token *)token_to_find->content)->text, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (-1);
}
