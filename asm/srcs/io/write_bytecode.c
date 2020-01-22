/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:21 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:41:22 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "g_op.h"

static ssize_t	(*pick_write_func_big_endian(void))
	(int fd, const void *data, size_t size)
{
	uint16_t	x;

	x = 1;
	if (*(uint8_t *)&x)
		return (write_swap_endian);
	else
		return (write);
}

static char		*get_cor_filename(char *filename)
{
	char	*file_to_write;
	size_t	len;

	len = ft_strlen(filename);
	if (!(file_to_write = ft_strnew(len + 2)))
		return ((void *)ft_msg(strerror(ENOMEM), NULL, 0, STDERR_FILENO));
	ft_strncpy(file_to_write, filename, len - 1);
	ft_strcpy(file_to_write + len - 1, "cor");
	return (file_to_write);
}

static void		write_magic_name_comment_size(int fd, t_file *file,
		ssize_t (*write_wrapper)(int fd, const void *data, size_t size))
{
	write_unsigned_int(fd, COREWAR_EXEC_MAGIC, write_wrapper);
	write(fd, ((t_token *)file->name->content)->bin,
			((t_token *)file->name->content)->bin_size);
	write_n_bytes(fd, 0, PROG_NAME_LENGTH
			- ((t_token *)file->name->content)->bin_size);
	write_unsigned_int(fd, 0, write_wrapper);
	write_unsigned_int(fd, file->size, write_wrapper);
	write(fd, ((t_token *)file->comment->content)->bin,
			((t_token *)file->comment->content)->bin_size);
	write_n_bytes(fd, 0, COMMENT_LENGTH
			- ((t_token *)file->comment->content)->bin_size);
	write_unsigned_int(fd, 0, write_wrapper);
}

static void		write_instructions(int fd, t_file *file,
		ssize_t (*write_wrapper)(int fd, const void *data, size_t size))
{
	t_list			*current;
	t_instruction	*instr;

	current = file->tokens;
	while (current)
	{
		if (((t_token *)current->content)->type == rx_op)
		{
			instr = ((t_token *)current->content)->bin;
			write(fd, &instr->code, sizeof(instr->code));
			if (g_op[instr->code].coding_arg_type)
				write(fd, &instr->coding_byte, sizeof(instr->coding_byte));
			if (instr->coding_byte & ARG1)
				write_wrapper(fd, &instr->args[0], instr->arg_sizes[0]);
			if (instr->coding_byte & ARG2)
				write_wrapper(fd, &instr->args[1], instr->arg_sizes[1]);
			if (instr->coding_byte & ARG3)
				write_wrapper(fd, &instr->args[2], instr->arg_sizes[2]);
		}
		current = current->next;
	}
}

int				write_bytecode(char *filename, t_file *file)
{
	static ssize_t	(*write_wrapper)(int fd, const void *data, size_t size);
	char			*file_to_write;
	int				fd;

	if (!write_wrapper)
		write_wrapper = pick_write_func_big_endian();
	if (!(file_to_write = get_cor_filename(filename)))
		return (-1);
	errno = 0;
	fd = open(file_to_write, WB_O_FLAGS, WB_O_MODE);
	if (fd == -1)
		ft_msg(strerror(errno), file_to_write, -1, STDERR_FILENO);
	else
	{
		write_magic_name_comment_size(fd, file, write_wrapper);
		write_instructions(fd, file, write_wrapper);
		if (close(fd) == -1)
			ft_msg(strerror(errno), file_to_write, -1, STDERR_FILENO);
	}
	free(file_to_write);
	return (!errno ? 0 : -1);
}
