/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:30:18 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:31:29 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	int			i;
	t_fa_state	*regexes[rx_total_number];

	if (argc <= 1)
		return (ft_msg(MSG_NO_ARGS"\n"MSG_USAGE, NULL, 1, STDERR_FILENO));
	if (compile_regexes(regexes) == -1)
		return (ft_msg(strerror(ENOMEM), NULL, 1, STDERR_FILENO));
	i = 0;
	while (++i < argc)
	{
		ft_putstr_fd(i == 1 ? "" : "\n", STDOUT_FILENO);
		ft_msg(MSG_PARSE, argv[i], 0, STDOUT_FILENO);
		if (process_file(argv[i], regexes) == -1)
			ft_msg(MSG_FILE_ERROR, argv[i], 1, STDERR_FILENO);
		else
			ft_msg(MSG_FILE_SUCCESS, argv[i], 0, STDOUT_FILENO);
	}
	del_regexes(regexes, rx_total_number);
	return (0);
}
