/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:38:12 by jrobin-h          #+#    #+#             */
/*   Updated: 2018/12/19 12:38:13 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rbt	*ft_rbtmin(t_rbt *root)
{
	if (!root)
		return (NULL);
	while (root->left)
		root = root->left;
	return (root);
}