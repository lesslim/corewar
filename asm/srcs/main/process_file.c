/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:18 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:30:18 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_correct_filename(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	return (len > 2 && filename[len - 1] == 's' && filename[len - 2] == '.');
}

static int	clear_file(char **text, t_file *file, int exit_code)
{
	if (*text)
	{
		free(*text);
		*text = NULL;
	}
	if (file->tokens)
	{
		file->name = NULL;
		file->comment = NULL;
		file->size = 0;
		ft_lstdel(&file->tokens, del_token);
	}
	return (exit_code);
}

int			process_file(char *filename, t_fa_state **regexes)
{
	char	*text;
	t_file	file;

	if (!is_correct_filename(filename))
		return (ft_msg(MSG_INVAL_FILENAME, filename, -1, STDERR_FILENO));
	if (!(text = read_file(filename)))
		return (ft_msg(strerror(errno), filename, -1, STDERR_FILENO));
	ft_bzero(&file, sizeof(t_file));
	if (!(file.tokens = tokenize(text, regexes)))
		return (clear_file(&text, &file, -1));
	if (analyze(&file) == -1)
		return (clear_file(&text, &file, -1));
	if (write_bytecode(filename, &file) == -1)
		return (clear_file(&text, &file, -1));
	return (clear_file(&text, &file, 0));
}
