/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 22:54:56 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/06 00:05:33 by rbarbero         ###   ########.fr       */
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
** The order of the first ten entries is important.
** It's linked with g_op_token.
** PLEASE DO NOT CHANGE THAT!
*/

enum							e_token
{
	AND_IF,
	OR_IF,
	DSEMI,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,
	TOKEN,
	IO_NUMBER,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	CONTROL
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
#endif
