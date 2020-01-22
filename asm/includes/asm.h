/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:28:10 by jrobin-h          #+#    #+#             */
/*   Updated: 2019/10/23 15:36:50 by jrobin-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "regex.h"

# include "op.h"
# include "regex_op.h"

/*
**	============================== CONSTANTS ===================================
*/

# define ASM_NAME			"asm"

# define MAX_SRC_FILE_SIZE	1048576

# define MSG_ANC_ERROR		"analyzer_name_and_comment: Internal error"
# define MSG_CA_RAISE		"raise: Argument token is NULL"
# define MSG_CAC_ARG_ID		"Unexpected argument, id"
# define MSG_CMNT_TOO_LONG	"Champ's comment too long"
# define MSG_DUPLICATE		"Duplicate symbols"
# define MSG_DUPLICATE_CMNT	"Duplicate comment"
# define MSG_DUPLICATE_NAME	"Duplicate name"
# define MSG_EMPTY			"No tokens found"
# define MSG_EMPTY_NC		"Empty name or comment"
# define MSG_FILE_ERROR		"Error parsing file"
# define MSG_FILE_SUCCESS	"Successfully parsed file"
# define MSG_FILE_TOO_BIG	"File exceeds max source file size"
# define MSG_GNL_ERROR		"get_n_labels: Internal_error"
# define MSG_INVAL_ARGNO	"Invalid argument number"
# define MSG_INVAL_FILENAME	"Invalid extension, must be .s"
# define MSG_INVAL_REGNO	"Invalid registry number"
# define MSG_NAME_TOO_LONG	"Champ's name too long"
# define MSG_NO_ARGS		"Missing arguments"
# define MSG_NO_COMMENT		"Missing champion's comment"
# define MSG_NO_INSTR		"No instructions found"
# define MSG_NO_NAME		"Missing champ's name"
# define MSG_OVERUNDERFLOW	"Possible overflow/underflow"
# define MSG_PARSE			"Parsing file..."
# define MSG_TOO_MANY_ARGS	"Too many arguments"
# define MSG_UNEXPECTED_ARG	"Unexpected arguments"
# define MSG_UNEXPECTED_EOF	"Unexpected end of file"
# define MSG_UNEXPECTED_TOK	"Unexpected token"
# define MSG_UNKNOWN_LAB	"Undefined label"
# define MSG_UNKNOWN_OP		"Unknown operator"
# define MSG_UNKNOWN_SEQ	"Unknown sequence"
# define MSG_USAGE			"Usage: asm file0.s file1.s ... fileN.s"

# define WB_O_FLAGS			(O_WRONLY | O_APPEND | O_CREAT | O_TRUNC)
# define WB_O_MODE			(S_IRWXU | S_IXGRP | S_IRGRP | S_IXOTH | S_IROTH)

# define ARG1				0b11000000u
# define ARG2				0b00110000u
# define ARG3				0b00001100u

/*
**	=========================== DATA STRUCTURES ================================
*/

typedef struct	s_token
{
	enum e_regexes	type;
	char			*text;
	void			*bin;
	size_t			bin_size;
}				t_token;

typedef struct	s_file
{
	t_list		*name;
	t_list		*comment;
	uint32_t	size;
	t_list		*tokens;
}				t_file;

typedef union	u_arg
{
	int8_t	byte1;
	int16_t	byte2;
	int32_t	byte4;
}				t_arg;

typedef	struct	s_instruction
{
	uint8_t			code;
	uint8_t			coding_byte;
	uint8_t			op_size;
	uint8_t			arg_sizes[3];
	t_arg			args[3];
}				t_instruction;

/*
**	============================== FUNCTIONS ===================================
*/

/*
**	analyze ====================================================================
*/

int				analyze(t_file *file);
int				analyzer_name_and_comment(t_list **token_lst);
int				analyzer_op(t_list **token_lst);
int				fill_file_data(t_file *file, t_htab **labels);
long			ft_ltoi_safe(const char *str);
int				get_coding_byte(t_list **token_lst, t_instruction *instr,
		t_list *instr_token_lst);
int				is_argument(t_token *token);
int				write_args(t_list *current_token, t_htab *labels);
int				write_argument_type(t_instruction *instr, t_list *token_lst);

/*
**	data_handlers ==============================================================
*/

void			clear_token(t_token *token);
int				compile_regexes(t_fa_state **regexes);
void			del_regexes(t_fa_state **regexes, int n_regexes);
void			del_token(void **content, size_t *size);

/*
**	helpers ====================================================================
*/

void			append_to_list(t_list **head, t_list *newlst, int lst_is_token);

/*
**	io =========================================================================
*/

long			ft_msg(char *msg, char *arg, int code, int fd);
int				token_error(char *msg, t_list *token);
char			*read_file(char *filename);
int				write_bytecode(char *filename, t_file *file);
void			write_n_bytes(int fd, unsigned char byte, unsigned int n);
ssize_t			write_swap_endian(int fd, const void *data, size_t size);
void			write_unsigned_int(int fd, int n,
		ssize_t (*write_wrapper)(int fd, const void *data, size_t size));

/*
**	main =======================================================================
*/

int				process_file(char *filename, t_fa_state **regexes);
t_list			*tokenize(char *text, t_fa_state **regexes);

#endif
