/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_op.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:28:11 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:28:11 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_OP_H
# define G_OP_H

# define TOTAL_OPS 16

typedef struct		s_allowed_arg_types
{
	unsigned int	t_reg : 1;
	unsigned int	t_dir : 1;
	unsigned int	t_ind : 1;
}					t_allowed_arg_types;

typedef struct		s_op
{
	char				op_name[8];
	unsigned int		n_args : 2;
	unsigned int		coding_arg_type : 1;
	unsigned int		t_dir_2o : 1;
	t_allowed_arg_types	arg_types[3];
}					t_op;

extern const t_op	g_op[TOTAL_OPS + 1];

#endif
