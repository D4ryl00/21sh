/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:48:09 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 13:20:43 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "sh.h"
# include "parser.h"
# include "jobcontrol.h"

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
int								eval_complete_commands(
		t_ast_complete_commands *cc , struct s_job *job);
int								eval_complete_command(
		t_ast_complete_command *cc, struct s_job *job);
int								eval_list(t_ast_list *list, struct s_job *job);
int								eval_and_or(t_ast_and_or *and_or,
		struct s_job *job);
int								eval_pipeline(t_ast_pipeline *pipeline,
		struct s_job *job);
int								eval_pipe_sequence(t_ast_pipe_sequence *ps,
		struct s_job *job);
int								eval_command(t_ast_command *command,
		struct s_job *job);
int								eval_compound_command(
		t_ast_compound_command *cc, struct s_job *job);
int								eval_simple_command(t_ast_simple_command *sc,
		struct s_job *job);
int								eval_subshell(t_ast_subshell *subshell,
		struct s_job *job);
int								cmd_select_type(char **av, struct s_job *job,
		char **env);
int								is_builtin_cmd(char **av);
int								run_builtin_cmd(char **av);
int								is_special_builtin_cmd(char **av);
int								run_special_builtin_cmd(char **av);
int								is_utility_cmd(char **av);
int								run_utility_cmd(char **av);
int								run(char *path, char **av, struct s_job *job,
		char **env);
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
