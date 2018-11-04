/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:53:52 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/04 12:41:19 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "sh.h"
# include "lexer.h"

# define IO_NUMBER_SIZE	4

typedef struct						s_ast_and_or t_ast_and_or;

/*
** Structures for the AST
*/

typedef struct						s_ast_cmd_name
{
	char							*word;
}									t_ast_cmd_name;

typedef struct						s_ast_cmd_word
{
	char							*word;
}									t_ast_cmd_word;

typedef struct						s_ast_filename
{
	char							*word;
}									t_ast_filename;

typedef struct						s_ast_io_file
{
	enum e_token					op;
	t_ast_filename					*filename;
}									t_ast_io_file;

typedef struct						s_ast_here_end
{
	char							*word;
}									t_ast_here_end;

typedef struct						s_ast_io_here
{
	enum e_token					op;
	t_ast_here_end					*here_end;
}									t_ast_io_here;

typedef struct						s_ast_io_redirect
{
	char							io_number[IO_NUMBER_SIZE];
	t_ast_io_file					*io_file;
	t_ast_io_here					*io_here;
}									t_ast_io_redirect;

typedef struct						s_ast_redirect_list
{
	t_list							*redirect_list;
	t_ast_io_redirect				*io_redirect;
}									t_ast_redirect_list;

typedef struct						s_ast_cmd_suffix
{
	t_ast_io_redirect				*io_redirect;
	char							*word;
	struct s_ast_cmd_suffix			*cmd_suffix;
}									t_ast_cmd_suffix;

typedef struct						s_ast_cmd_prefix
{
	t_ast_io_redirect				*io_redirect;
	char							*assignment_word;
	struct s_ast_cmd_prefix			*cmd_prefix;
}									t_ast_cmd_prefix;

typedef struct						s_ast_simple_command
{
	t_ast_cmd_prefix				*cmd_prefix;
	t_ast_cmd_word					*cmd_word;
	t_ast_cmd_name					*cmd_name;
	t_ast_cmd_suffix				*cmd_suffix;
}									t_ast_simple_command;

typedef struct						s_ast_newline_list
{
	char							nl;
	struct s_ast_newline_list		*newline_list;
}									t_ast_newline_list;

typedef struct						s_ast_linebreak
{
	t_ast_newline_list				*newline_list;
}									t_ast_linebreak;

typedef struct						s_ast_separator_op
{
	char							c;
}									t_ast_separator_op;

typedef struct						s_ast_separator
{
	t_ast_separator_op				*separator_op;
	t_ast_linebreak					*linebreak;
	t_ast_newline_list				*newline_list;
}									t_ast_separator;

typedef struct						s_ast_term
{
	t_ast_and_or					*and_or;
	t_ast_separator					*separator;
	struct s_ast_term				*term;
}									t_ast_term;

typedef struct						s_ast_compound_list
{
	t_ast_linebreak					*linebreak;
	t_ast_term						*term;
	t_ast_separator					*separator;
}									t_ast_compound_list;

typedef struct						s_ast_subshell
{
	t_ast_compound_list				*compound_list;
}									t_ast_subshell;

typedef struct						s_ast_compound_command
{
	t_ast_subshell					*subshell;
}									t_ast_compound_command;

typedef struct						s_ast_command
{
	t_ast_simple_command			*simple_command;
	t_ast_compound_command			*compound_command;
	t_ast_redirect_list				*redirect_list;
}									t_ast_command;

typedef struct						s_ast_pipe_sequence
{
	t_ast_linebreak					*linebreak;
	t_ast_command					*command;
	struct s_ast_pipe_sequence		*pipe_sequence;
}									t_ast_pipe_sequence;

typedef struct						s_ast_pipeline
{
	char							bang;
	t_ast_pipe_sequence				*pipe_sequence;
}									t_ast_pipeline;

typedef struct						s_ast_and_or
{
	char							*op;
	t_ast_pipeline					*pipeline;
	t_ast_linebreak					*linebreak;
	struct s_ast_and_or				*and_or;
}									t_ast_and_or;

typedef struct						s_ast_list
{
	t_ast_and_or					*and_or;
	t_ast_separator_op				*separator_op;
	struct s_ast_list				*list;
}									t_ast_list;

typedef	struct						s_ast_complete_command
{
	t_ast_list						*list;
	t_ast_separator_op				*separator_op;
}									t_ast_complete_command;

typedef struct						s_ast_complete_commands
{
	struct s_ast_complete_command	*complete_command;
	t_ast_newline_list				*newline_list;
	struct s_ast_complete_commands	*complete_commands;
}									t_ast_complete_commands;

typedef struct						s_ast_program
{
	t_ast_linebreak					*linebreak;
	t_ast_complete_commands			*complete_commands;
	t_ast_linebreak					*post_linebreak;
}									t_ast_program;

/*
** PROTOTYPES
*/

int									ast_cmd_name(t_ast_cmd_name **name
		, t_list **tokens);
void								free_ast_cmd_name(t_ast_cmd_name *cmd_name);
int									ast_cmd_word(t_ast_cmd_word **word
		, t_list **tokens);
void								free_ast_cmd_word(t_ast_cmd_word *cmd_word);
int									ast_filename(t_ast_filename **filename
		, t_list **tokens);
void								free_ast_filename(t_ast_filename *filename);
int									ast_io_file(t_ast_io_file **file
		, t_list **tokens);
void								free_ast_io_file(t_ast_io_file *file);
int									ast_here_end(t_ast_here_end **here_end
		, t_list **tokens);
void								free_ast_here_end(t_ast_here_end *here_end);
int									ast_io_here(t_ast_io_here **here
		, t_list **tokens);
void								free_ast_io_here(t_ast_io_here *io_here);
int									ast_io_redirect(t_ast_io_redirect **redirect
		, t_list **tokens);
void								free_ast_io_redirect(t_ast_io_redirect
		*redirect);
int									ast_cmd_suffix(t_ast_cmd_suffix **suffix
		, t_list **tokens);
void								free_ast_cmd_suffix(t_ast_cmd_suffix
		*suffix);
int									ast_cmd_prefix(t_ast_cmd_prefix **prefix
		, t_list **tokens);
void								free_ast_cmd_prefix(t_ast_cmd_prefix
		*prefix);
int									ast_simple_command(t_ast_simple_command **sc
		, t_list **tokens);
void								free_ast_simple_command(t_ast_simple_command
		*sc);
int									ast_command(t_ast_command **command
		, t_list **tokens);
void								free_ast_command(t_ast_command *command);
int									ast_separator_op(t_ast_separator_op **s_op
		, t_list **tokens);
void								free_ast_separator_op(t_ast_separator_op
		*s_op);
int									ast_newline_list(t_ast_newline_list
		**nl_list, t_list **tokens);
void								free_ast_newline_list(t_ast_newline_list
		*newline_list);
int									ast_linebreak(t_ast_linebreak **linebreak
		, t_list **tokens);
void								free_ast_linebreak(t_ast_linebreak
		*linebreak);
int									ast_pipe_sequence(t_ast_pipe_sequence **ps
		, t_list **tokens);
void								free_ast_pipe_sequence(t_ast_pipe_sequence
		*ps);
int									ast_pipeline(t_ast_pipeline **pipeline
		, t_list **tokens);
void								free_ast_pipeline(t_ast_pipeline *pipeline);
int									ast_and_or(t_ast_and_or **and_or, t_list
		**tokens);
void								free_ast_and_or(t_ast_and_or *and_or);
int									ast_list(t_ast_list **list
		, t_list **tokens);
void								free_ast_list(t_ast_list *list);
int									ast_complete_command(t_ast_complete_command
		**cc, t_list **tokens);
void								free_ast_complete_command(
		t_ast_complete_command *cc);
int									ast_complete_commands(
		t_ast_complete_commands **cc, t_list **tokens);
void								free_ast_complete_commands(
		t_ast_complete_commands *cc);
int									ast_program(t_ast_program **program
		, t_list *tokens);
void								free_ast_program(t_ast_program *program);
int									ast_compound_command(
		t_ast_compound_command **cc, t_list **tokens);
void								free_ast_compound_command(
		t_ast_compound_command *cc);
int									ast_subshell(t_ast_subshell **subshell
		, t_list **tokens);
void								free_ast_subshell(t_ast_subshell *subshell);
int									ast_compound_list(t_ast_compound_list **cl
		, t_list **tokens);
void								free_ast_compound_list(
		t_ast_compound_list *cl);
int									ast_term(t_ast_term **term
		, t_list **tokens);
void								free_ast_term(t_ast_term *term);
int									ast_separator(t_ast_separator **separator
		, t_list **tokens);
void								free_ast_separator(
		t_ast_separator *separator);
#endif
