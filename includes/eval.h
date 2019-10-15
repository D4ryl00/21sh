/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:48:09 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/15 14:47:41 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "sh.h"
# include "parser.h"
# include "jobcontrol.h"

# define QUOTE_REMOVAL 0x1

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
		t_ast_complete_commands *cc);
int								eval_complete_command(
		t_ast_complete_command *cc);
int								eval_list(t_ast_list *list, int async);
int								eval_and_or(t_ast_and_or *and_or, int async);
int								eval_pipeline(t_ast_pipeline *pipeline);
int								eval_pipe_sequence(t_ast_pipe_sequence *ps);
void							set_pipe_struct(t_pipe *pipe, int rd, int wr);
int								duplicate_fd(t_pipe_env *pipe_env);
int								eval_command(t_ast_command *command);
int								eval_compound_command(
		t_ast_compound_command *cc);
int								eval_simple_command(t_ast_simple_command *sc);
int								eval_subshell(t_ast_subshell *subshell);
void							get_pipeline_cmd_name(t_ast_pipeline *pipeline,
		t_buf *pipeline_cmd_name);
void							get_pipe_sequence_cmd_name(
		t_ast_pipe_sequence *ps, t_buf *ps_cmd_name);
void							get_command_cmd_name(t_ast_command *command,
		t_buf *command_cmd_name);
void							get_simple_command_cmd_name(
		t_ast_simple_command *sc, t_buf *sc_cmd_name);
void							get_compound_command_cmd_name(
		t_ast_compound_command *cc, t_buf *sc_cmd_name);
void							get_subshell_cmd_name(t_ast_subshell *subshell,
		t_buf *sc_subshell_name);
int								cmd_select_type(char **av, char **env);
int								is_builtin_cmd(char **av);
int								run_builtin_cmd(char **av);
int								is_special_builtin_cmd(char **av);
int								run_special_builtin_cmd(char **av);
int								is_utility_cmd(char **av);
int								run_utility_cmd(char **av);
int								run(char *path, char **av, char **env);
int								do_eval_redirs(t_ast_simple_command *sc
		, t_list **redirs);
char							*redir_get_filename(const char *str);
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
int								word_expansion(t_list **out, const char *in,
		int options);
void							word_expansion_del_node(void *content,
		size_t size);
int								quote_removal(t_list **out, const char *in);
#endif
