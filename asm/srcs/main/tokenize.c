/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:18 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:18 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		*tokenize_error(char *msg, char *text_ptr)
{
	token_error(msg, NULL);
	if (text_ptr)
	{
		ft_putstr_fd(ASM_NAME": "MSG_UNKNOWN_SEQ": ", STDERR_FILENO);
		while (*text_ptr && *text_ptr != '\n')
		{
			ft_putchar_fd(*text_ptr, STDERR_FILENO);
			++text_ptr;
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (NULL);
}

static char		*strdup_from_addr(char *start, char *end)
{
	char	*out;

	if (!start || !end || end <= start || !(out = ft_strnew(end - start)))
		return (NULL);
	return (ft_memcpy(out, start, end - start));
}

static t_list	*get_next_token(char **textptr, t_fa_state **regexes)
{
	t_list	*token_lst;
	t_token	token;
	char	*match_end;

	ft_bzero(&token, sizeof(token));
	while (token.type < rx_total_number)
	{
		if ((match_end = ft_regex_pmatch(regexes[token.type], *textptr)))
			break ;
		++(token.type);
	}
	if (token.type == rx_total_number)
		return (tokenize_error(MSG_UNKNOWN_SEQ, *textptr));
	if (token.type != rx_ws
			&& token.type != rx_comment && token.type != rx_arg_sep
			&& !(token.text = strdup_from_addr(*textptr, match_end)))
		return ((void *)(long)ft_msg(strerror(ENOMEM), NULL, 0, STDERR_FILENO));
	if (!(token_lst = ft_lstnew(&token, sizeof(t_token))))
		clear_token(&token);
	*textptr = match_end;
	return (token_lst ? token_lst :
			(void *)ft_msg(strerror(ENOMEM), NULL, 0, STDERR_FILENO));
}

static int		is_skippable_token(t_token *token)
{
	return (token->type == rx_ws || token->type == rx_comment);
}

t_list			*tokenize(char *text, t_fa_state **regexes)
{
	t_list	*tokens;
	t_list	*new_token;
	char	*textptr;

	tokens = NULL;
	textptr = text;
	append_to_list(NULL, NULL, 1);
	while (*textptr)
	{
		if (!(new_token = get_next_token(&textptr, regexes)))
		{
			ft_lstdel(&tokens, del_token);
			return (NULL);
		}
		if (is_skippable_token(new_token->content))
			ft_lstdelone(&new_token, del_token);
		else
			append_to_list(&tokens, new_token, 1);
	}
	return (tokens ? tokens :
			(void *)ft_msg(MSG_EMPTY, NULL, 0, STDERR_FILENO));
}
