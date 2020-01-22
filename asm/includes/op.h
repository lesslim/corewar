/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:28:11 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:29:20 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
**	CAN BE CHANGED EASILY ======================================================
*/

/*
**	The use of unPP_refixed format macros is deprecated, use the PP_ ones.
**	The syntax is described at regex.h
*/

# define PP_COMMENT_CHAR			"#"
# define PP_LABEL_CHAR				":"
# define PP_DIRECT_CHAR				"%"
# define PP_SEPARATOR_CHAR			","

# define PP_LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define PP_NAME_CMD_STRING			"[.]name"
# define PP_COMMENT_CMD_STRING		"[.]comment"

# define REG_NUMBER					16

# define PROG_NAME_LENGTH			(128)
# define COMMENT_LENGTH				(2048)

/*
**	CHANGING COULD REQUIRE CODE UPDATE =========================================
*/

# define REG_CODE					1
# define DIR_CODE					2
# define IND_CODE					3

# define IND_SIZE					2
# define REG_NUMBER_SIZE			1
# define REG_CONTENT_SIZE			4
# define DIR_SIZE					REG_CONTENT_SIZE

# define COREWAR_EXEC_MAGIC			0xea83f3

/*
**	DEPRECATED =================================================================
*/

# define COMMENT_CHAR				'#'
# define LABEL_CHAR					':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR				','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING			".comment"

typedef char	t_arg_type;

# define T_REG						1
# define T_DIR						2
# define T_IND						4
# define T_LAB						8

typedef struct	s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}				t_header;

/*
**	VM_ONLY ====================================================================
*/

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE					(4 * 1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE				(MEM_SIZE / 6)

# define CYCLE_TO_DIE				1536
# define CYCLE_DELTA				50
# define NBR_LIVE					21
# define MAX_CHECKS					10

#endif
