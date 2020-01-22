/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:24 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:24 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	append_to_list(t_list **head, t_list *newlst, int lst_is_token)
{
	static t_list *tail;

	if (!head || !newlst)
	{
		tail = NULL;
		if (lst_is_token)
			token_error(NULL, NULL);
		return ;
	}
	if (!tail)
	{
		tail = newlst;
		*head = newlst;
		if (lst_is_token)
			token_error(NULL, newlst);
	}
	else
		tail = ft_lstappend(tail, newlst);
}
