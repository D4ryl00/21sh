/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:50:04 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/19 17:00:53 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"
#include <unistd.h>

static void	set_pipe(t_pipe *pipe, int rd, int wr)
{
	pipe->rd = rd;
	pipe->wr = wr;
}

/*
**	Get fd of an opened pipe and dup them on stdin or stdout.
*/

static int	run_eval_pipe(t_pipe_env *pipe_env)
{
	if ((pipe_env->input.rd != -1)
			&& (dup2(pipe_env->input.rd, pipe_env->input.wr) == -1))
		return (return_perror(EDUP, NULL));
	if ((pipe_env->output.rd != -1)
			&& (dup2(pipe_env->output.wr, pipe_env->output.rd) == -1))
		return (return_perror(EDUP, NULL));
	return (0);
}

static int	eval_pipe(t_ast_pipe_sequence *ps, t_pipe_env *pipe_env)
{
	int		status;
	int		pipe_fd[2];

	status = 0;
	if (pipe(pipe_fd) == -1)
		return (return_perror(EPIPE, NULL));
	set_pipe(&(pipe_env->output), 1, pipe_fd[1]);
	if ((pipe_env->fd_cpy[1] = dup(1)) == -1)
		return (return_perror(EDUP, NULL));
	if (run_eval_pipe(pipe_env) == -1)
		return (-1);
	if (newprocess(g_jobctrl.current_job) == -1)
		return (-1);
	//need for no waiting
	g_jobctrl.current_job->nowait = 1;
	status = eval_command(ps->command);
	if (pipe_env->input.rd != -1)
		close(pipe_env->input.rd);
	if (pipe_env->fd_cpy[0] != -1 && dup2(pipe_env->fd_cpy[0], 0) == -1)
		return (return_perror(EDUP, NULL));
	pipe_env->fd_cpy[0] = -1;
	close(pipe_fd[1]);
	if (dup2(pipe_env->fd_cpy[1], 1) == -1)
		return (return_perror(EDUP, NULL));
	set_pipe(&(pipe_env->output), -1, -1);
	if ((pipe_env->fd_cpy[0] = dup(0)) == -1)
		return (return_perror(EDUP, NULL));
	set_pipe(&(pipe_env->input), pipe_fd[0], 0);
	return (status);
}

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

int			eval_pipe_sequence(t_ast_pipe_sequence *ps)
{
	int				status;
	t_pipe_env		pipe_env;
	int				multipipes;

	status = 0;
	multipipes = 0;
	set_pipe(&(pipe_env.input), -1, -1);
	set_pipe(&(pipe_env.output), -1, -1);
	pipe_env.fd_cpy[0] = -1;
	while (ps)
	{
		if (ps->pipe_sequence)
		{
			multipipes = 1;
			status = eval_pipe(ps, &pipe_env);
		}
		// doit checker le status ci-dessus et close les pipes et quitter si -1
		else
		{
			if (multipipes)
			{
				if (newprocess(g_jobctrl.current_job) == -1)
					return (-1);
				g_jobctrl.current_job->nowait = 0;
			}
			if (run_eval_pipe(&pipe_env) == -1)
				return (-1);
			status = eval_command(ps->command);
			if (pipe_env.input.rd != -1)
				close(pipe_env.input.rd);
			if (pipe_env.fd_cpy[0] != -1 && dup2(pipe_env.fd_cpy[0], 0) == -1)
				return (return_perror(EDUP, NULL));
			pipe_env.fd_cpy[0] = -1;
			set_pipe(&(pipe_env.input), -1, -1);
			if (tcsetpgrp(g_termcaps.fd, g_shell.pgid) == -1)
				return_perror(EOTHER, "eval_pipe_sequence: tcsetpgrp error");
		}
		ps = ps->pipe_sequence;
	}
	return (status);
}
