/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_swap_endian.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:21 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:41:30 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

ssize_t	write_swap_endian(int fd, const void *data, size_t size)
{
	size_t	i;

	i = size;
	while (i > 0)
	{
		if (write(fd, (unsigned char *)data + (i - 1), 1) == -1)
			return (-1);
		--i;
	}
	return (size);
}
