/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:57:28 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/09 22:28:49 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			reader(int fd, int size, char *buf)
{
	int ret;

	if (!(ret = read(fd, buf, size)) || ret != size)
		return (0);
	return (1);
}

uint32_t	numreader(int fd, int size)
{
	int			ret;
	uint32_t	buf;

	if (!(ret = read(fd, &buf, size)) || ret != size)
		return (-1);
	reverse_bytes(&buf, size);
	return (buf);
}

int			read_champion_three(char *nll, int fd, t_champ *champion)
{
	if (!reader(fd, 4, nll))
	{
		ft_putstr_fd("no another NULL\n", STDERR_FILENO);
		return (0);
	}
	if (!(champion->code = (char*)ft_memalloc(sizeof(char) * champion->size))
	|| !(reader(fd, champion->size, champion->code)) || reader(fd, 1, nll))
	{
		ft_putstr_fd("invalid code\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int			read_champion_two(char *nll, int fd, t_champ *champion)
{
	if (!reader(fd, 4, nll))
	{
		ft_putstr_fd("no NULL\n", STDERR_FILENO);
		return (0);
	}
	if (!((champion->size = numreader(fd, 4)) + 1) ||
	(int)champion->size > CHAMP_MAX_SIZE)
	{
		ft_putstr_fd("wrong champ exec code size\n", STDERR_FILENO);
		return (0);
	}
	if (!(champion->comment = (char*)ft_memalloc(sizeof(char) *
	COMMENT_LENGTH + 1)) || !reader(fd, COMMENT_LENGTH, champion->comment))
	{
		ft_putstr_fd("bad comment\n", STDERR_FILENO);
		return (0);
	}
	return (read_champion_three(nll, fd, champion));
}

int			read_champion(char *filename, t_champ *champion)
{
	int		fd;
	char	nll[4];

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_putstr_fd("can't open ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
	}
	if (!((champion->header = numreader(fd, 4)) + 1) ||
	champion->header != COREWAR_EXEC_MAGIC)
	{
		ft_putstr_fd("invalid header\n", STDERR_FILENO);
		return (0);
	}
	if (!(champion->name = (char*)ft_memalloc(sizeof(char) *
	PROG_NAME_LENGTH + 1)) || !reader(fd, PROG_NAME_LENGTH, champion->name))
	{
		ft_putstr_fd("champ has an invalid name\n", STDERR_FILENO);
		return (0);
	}
	return (read_champion_two(nll, fd, champion));
}
