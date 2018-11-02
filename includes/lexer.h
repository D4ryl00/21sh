/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 22:54:56 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 14:40:09 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "sh.h"

extern char						*g_op_token[];
extern char						*g_control_operator[];

/*
** TYPES
*/

/*
** Possible token types
*/

enum							e_token
{
	TOKEN,
	WORD,
	IO_NUMBER,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	OPERATOR
};

typedef struct					s_token
{
	enum e_token				type;
	char						*content;
}								t_token;

/*
** PROTOTYPES
*/

t_list							*lexer(t_input *input);
void							insert_token(t_list **tokens, char *token
		, enum e_token type);
int								is_operator(t_buf *buffer, char c
		, unsigned char f_params[2]);
int								operator_case(t_list **tokens, t_buf *buffer
	, t_input *input, unsigned char f_params[2]);
int								operator_start_case(t_list **tokens
	, t_buf *buffer, t_input *input, unsigned char f_params[2]);
int								sq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								bs_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								dq_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								dollar_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								bracket_expansion(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								variable_expansion(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								arithmetic_expansion(t_buf *buffer
		, t_input *input, unsigned char f_params[2]);
int								substitution_case(t_buf *buffer, t_input *input
		, unsigned char f_params[2], char close);
int								comment_input(t_input *input);
int								delimiter_case(t_list **tokens, t_buf *buffer
		, t_input *input, unsigned char f_params[2]);
int								add_char_new_token(t_buf *buffer, t_input *input
		, unsigned char f_params[2]);
int								add_char_to_token(t_buf *buffer
		, t_input *input);
enum e_token					get_op_type(char *str);
#endif
