/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:50:04 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/15 17:06:13 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"
#include <unistd.h>

void		get_pipe_sequence_cmd_name(t_ast_pipe_sequence *ps,
		t_buf *ps_cmd_name)
{
	int	multipipes;

	while (ps)
	{
		if (ps->pipe_sequence)
			multipipes = 1;
		else
			multipipes = 0;
		if (ps->command)
			get_command_cmd_name(ps->command, ps_cmd_name);
		if (multipipes)
			ft_buf_add_str(ps_cmd_name, " | ");
		ps = ps->pipe_sequence;
	}
}

static int	restore_fd(t_pipe_env *pipe_env, int *pipe_fd)
{
	if (pipe_env->input.rd != -1)
		close(pipe_env->input.rd);
	if (pipe_env->fd_cpy[0] != -1 && dup2(pipe_env->fd_cpy[0], 0) == -1)
		return (return_perror(EDUP, NULL, -1));
	pipe_env->fd_cpy[0] = -1;
	close(pipe_fd[1]);
	if (dup2(pipe_env->fd_cpy[1], 1) == -1)
		return (return_perror(EDUP, NULL, -1));
	set_pipe_struct(&(pipe_env->output), -1, -1);
	return (0);
}

static int	process_pipe_sequence(t_ast_pipe_sequence *ps, t_pipe_env *pipe_env)
{
	int		status;
	int		pipe_fd[2];

	status = 0;
	if (pipe(pipe_fd) == -1)
		return (return_perror(EPIPE, NULL, -1));
	set_pipe_struct(&(pipe_env->output), 1, pipe_fd[1]);
	if ((pipe_env->fd_cpy[1] = dup(1)) == -1)
		return (return_perror(EDUP, NULL, -1));
	if (duplicate_fd(pipe_env) == -1)
		return (-1);
	if (newprocess(g_jobctrl.current_job) == -1)
		return (-1);
	g_jobctrl.current_job->nowait = 1;
	status = eval_command(ps->command);
	if (g_jobctrl.current_job->child)
		exit(status);
	if (restore_fd(pipe_env, pipe_fd) == -1)
		return (-1);
	if ((pipe_env->fd_cpy[0] = dup(0)) == -1)
		return (return_perror(EDUP, NULL, -1));
	set_pipe_struct(&(pipe_env->input), pipe_fd[0], 0);
	return (status);
}

static int	process_final_pipe_sequence(t_ast_pipe_sequence *ps,
		t_pipe_env *pipe_env, int multipipes)
{
	int	status;

	if (multipipes)
	{
		if (newprocess(g_jobctrl.current_job) == -1)
			return (-1);
		g_jobctrl.current_job->nowait = 0;
	}
	if (duplicate_fd(pipe_env) == -1)
		return (-1);
	status = eval_command(ps->command);
	if (g_jobctrl.current_job->child)
		exit(status);
	if (pipe_env->input.rd != -1)
		close(pipe_env->input.rd);
	if (pipe_env->fd_cpy[0] != -1 && dup2(pipe_env->fd_cpy[0], 0) == -1)
		return (return_perror(EDUP, NULL, -1));
	pipe_env->fd_cpy[0] = -1;
	set_pipe_struct(&(pipe_env->input), -1, -1);
	if (tcsetpgrp(g_termcaps.fd, g_shell.pgid) == -1)
		return_perror(EOTHER, "tcsetpgrp error", -1);
	return (status);
}

int			eval_pipe_sequence(t_ast_pipe_sequence *ps)
{
	int				status;
	t_pipe_env		pipe_env;
	int				multipipes;

	status = 0;
	multipipes = 0;
	set_pipe_struct(&(pipe_env.input), -1, -1);
	set_pipe_struct(&(pipe_env.output), -1, -1);
	pipe_env.fd_cpy[0] = -1;
	while (ps)
	{
		if (ps->pipe_sequence)
		{
			multipipes = 1;
			if (process_pipe_sequence(ps, &pipe_env) == -1)
				return (-1);
		}
		else
			status = process_final_pipe_sequence(ps, &pipe_env, multipipes);
		ps = ps->pipe_sequence;
	}
	return (status);
}
