/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:48:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 05:58:34 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "sh.h"
# include "parser.h"

extern char						*g_builtin_cmd[];
extern char						*g_special_builtin_cmd[];
extern char						*g_utility_cmd[];

/*
** STRUCTURES
*/

typedef struct					s_pipe
{
	int							rd;
	int							wr;
}								t_pipe;

typedef struct					s_pipe_env
{
	t_ast_simple_command		*sc;
	t_pipe						input;
	t_pipe						output;
}								t_pipe_env;

/*
** PROTOTYPES
*/

int								eval(t_input *input);
int								eval_program(t_ast_program *program);
int								eval_pipeline(t_ast_pipeline *pipeline);
int								eval_pipe_sequence(t_ast_pipe_sequence *ps);
int								eval_command(t_ast_command *command
		, t_pipe_env *pipe_env);
int								eval_simple_command(t_ast_simple_command *sc
		, t_pipe_env *pipe_env);
int								cmd_select_type(char **av
		, t_pipe_env *pipe_env);
int								is_builtin_cmd(char **av);
int								run_builtin_cmd(char **av);
int								is_special_builtin_cmd(char **av);
int								run_special_builtin_cmd(char **av);
int								is_utility_cmd(char **av);
int								run_utility_cmd(char **av);
int								run(char *path, char **av
		, t_pipe_env *pipe_env);
int								run_eval_redirs(t_ast_simple_command *sc);
int								filename_redirect(t_ast_io_redirect
		*io_redirect, int io_number, char op, int mode);
int								fd_redirect(t_ast_io_redirect *io_redirect
		, int io_number, char op);
int								here_redirect(t_ast_io_redirect *io_redirect
		, int io_number);
#endif
