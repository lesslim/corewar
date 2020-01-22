/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_n_bytes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:21 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:21 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_n_bytes(int fd, unsigned char byte, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i++ < n)
		write(fd, &byte, 1);
}
