/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberon-s <rberon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 17:47:30 by rberon-s          #+#    #+#             */
/*   Updated: 2019/12/18 14:15:05 by rberon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_LEN				1

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define DELAY 8
# define DELAY_BOLD 100
# define BYTE_IN_STRING 64
# define BATTLEFIELD_Y 2
# define BATTLEFIELD_X 4
# define BATTLEFIELD_L (BYTE_IN_STRING * 3)
# define BATTLEFIELD_H (MEM_SIZE / 64)
# define INFO_X (BATTLEFIELD_L + 2 * BATTLEFIELD_X + 2)
# define INFO_Y BATTLEFIELD_Y
# define INFO_L (40)
# define INFO_H (BATTLEFIELD_H)
# define FRAME_H (BATTLEFIELD_H + BATTLEFIELD_Y * 2)
# define FRAME_L (INFO_X + INFO_L + BATTLEFIELD_X)
# define SUCCESS 0
# define FAIL 1

# define MSG_ERROR0 "Error of malloc\n"
# define MSG_ERROR1 "Can't read this files\n"
# define MSG_ERROR2 "Colors are not supported\n"
# define MSG_ERROR3 "Repeat of numbers\n"
# define MSG_ERROR4 "Code to big\n"
# define MSG_ERROR5 "Code to small\n"
# define MSG_ERROR6 "No magic\n"
# define MSG_ERROR7 "Differen byte size of programm\n"
# define MSG_ERROR8 "No null-terminator\n"
# define MSG_ERROR9 "No players\n"

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define ERROR					-1

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

#endif
