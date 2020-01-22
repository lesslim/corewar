/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:21 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:39:33 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*del_list_return_null(t_list *alst)
{
	ft_lstdel(&alst, ft_delcontent);
	return (NULL);
}

static char	*list_to_string_del_list(t_list *lst)
{
	char	*out;

	if (!lst)
	{
		errno = ENODATA;
		return (NULL);
	}
	out = ft_lsttostr(lst, '\0');
	ft_lstdel(&lst, ft_delcontent);
	return (out);
}

static char	*file_too_big(t_list **buflst)
{
	ft_lstdel(buflst, ft_delcontent);
	errno = ENOMEM;
	return ((void *)ft_msg(MSG_FILE_TOO_BIG, NULL, 0, STDERR_FILENO));
}

/*
**	ssize_t	bytes_read[2] = { just_now, in_total };
*/

char		*read_file(char *filename)
{
	int		fd;
	char	buf[GNL_BUFF_SIZE + 1];
	t_list	*buflst;
	t_list	*newlst;
	ssize_t	bytes_read[2];

	if (!filename || (fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	buflst = NULL;
	append_to_list(NULL, NULL, 0);
	ft_bzero(bytes_read, sizeof(bytes_read));
	while ((bytes_read[0] = read(fd, buf, GNL_BUFF_SIZE)) > 0)
	{
		if ((bytes_read[1] += bytes_read[0]) > MAX_SRC_FILE_SIZE)
			return (file_too_big(&buflst));
		buf[bytes_read[0]] = '\0';
		if (!(newlst = ft_lstnew(buf, bytes_read[0] + 1)))
			return (del_list_return_null(buflst));
		append_to_list(&buflst, newlst, 0);
	}
	close(fd);
	return (list_to_string_del_list(buflst));
}
