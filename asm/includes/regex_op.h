/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex_op.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:28:11 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:28:11 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_OP_H
# define REGEX_OP_H

# include "op.h"

# define AUX_LABEL_BODY		"["PP_LABEL_CHARS"]["PP_LABEL_CHARS"]*"
# define AUX_NUMBER			"[0-9][0-9]*"
# define AUX_SIGNED_NUMBER	"[-+]?"AUX_NUMBER
# define AUX_STRING			"\"[^\"]*\""

enum	e_regexes
{
	rx_skippable = 0,
	rx_ws_mf = 0,
	rx_ws,
	rx_comment,
	rx_champ_name,
	rx_champ_comment,
	rx_label,
	rx_arg_sep,
	rx_arg_l_ind,
	rx_arg_l_dir,
	rx_arg_reg,
	rx_arg_dir,
	rx_arg_ind,
	rx_op,
	rx_total_number
};

/*
**	rx_ws_mf -- whitespace forcing \n
**	rx_ws    --	whitespace not including \n
*/

# define RX_WS_MF			"\\S*\n\\s*"
# define RX_WS				"\\S\\S*"

# define RX_COMMENT			PP_COMMENT_CHAR"[^\n]*"
# define RX_CHAMP_NAME		PP_NAME_CMD_STRING"\\s*"AUX_STRING
# define RX_CHAMP_COMMENT	PP_COMMENT_CMD_STRING"\\s*"AUX_STRING
# define RX_LABEL			AUX_LABEL_BODY""PP_LABEL_CHAR
# define RX_ARG_SEP			PP_SEPARATOR_CHAR"\\S*"
# define RX_ARG_LABEL_IND	PP_LABEL_CHAR""AUX_LABEL_BODY
# define RX_ARG_LABEL_DIR	PP_DIRECT_CHAR""RX_ARG_LABEL_IND
# define RX_ARG_REG			"r"AUX_NUMBER
# define RX_ARG_DIR			PP_DIRECT_CHAR""AUX_SIGNED_NUMBER
# define RX_ARG_IND			AUX_SIGNED_NUMBER
# define RX_OP				"[a-z][a-z]*"

# define R0					RX_WS_MF
# define R1					RX_WS
# define R2					RX_COMMENT
# define R3					RX_CHAMP_NAME
# define R4					RX_CHAMP_COMMENT
# define R5					RX_LABEL
# define R6					RX_ARG_SEP
# define R7					RX_ARG_LABEL_IND
# define R8					RX_ARG_LABEL_DIR
# define R9					RX_ARG_REG
# define R10				RX_ARG_DIR
# define R11				RX_ARG_IND
# define R12				RX_OP

# define RX_RAW {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12}

# define RX_PATTERS			((char *[])RX_RAW)

#endif
