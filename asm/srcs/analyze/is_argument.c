/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argument.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:30 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:30 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	is_argument(t_token *token)
{
	return (token->type > rx_arg_sep && token->type < rx_op);
}
