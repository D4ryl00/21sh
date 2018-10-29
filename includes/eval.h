/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:48:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/29 10:35:40 by rbarbero         ###   ########.fr       */
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
	t_pipe						input;
	t_pipe						output;
	int							fd_cpy[2];
}								t_pipe_env;

typedef struct					s_redirs
{
	int	open;
	int	dup_src;
	int	dup_cpy;
}								t_redirs;

/*
** PROTOTYPES
*/

int								eval(t_input *input);
int								eval_program(t_ast_program *program);
int								eval_pipeline(t_ast_pipeline *pipeline
		, int wait);
int								eval_pipe_sequence(t_ast_pipe_sequence *ps
		, int wait);
int								eval_command(t_ast_command *command
		, int wait);
int								eval_simple_command(t_ast_simple_command *sc
		, int wait);
int								cmd_select_type(char **av, int wait
		, char **env);
int								is_builtin_cmd(char **av);
int								run_builtin_cmd(char **av);
int								is_special_builtin_cmd(char **av);
int								run_special_builtin_cmd(char **av);
int								is_utility_cmd(char **av);
int								run_utility_cmd(char **av);
int								run(char *path, char **av, int wait
		, char **env);
int								do_eval_redirs(t_ast_simple_command *sc
		, t_list **redirs);
int								filename_redirect_input(t_ast_io_redirect
		*io_redirect, int io_number, int mode, t_list **redirs);
int								filename_redirect_output(t_ast_io_redirect
		*io_redirect, int io_number, int mode, t_list **redirs);
int								fd_redirect(t_ast_io_redirect *io_redirect
		, int io_number, char op, t_list **redirs);
int								here_redirect(t_ast_io_redirect *io_redirect
		, int io_number, t_list **redirs);
void							t_redirs_init(t_redirs *redirs);
void							t_redirs_del(void *content
		, size_t content_size);
int								t_redirs_save_fd(t_redirs *save, int fd);
int								undo_redirs(t_list **redirs);
#endif
