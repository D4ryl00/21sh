/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:37:49 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/02 14:53:35 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <unistd.h>

static int	eval_simple_command(t_ast_simple_command *sc, t_pipe_env *pipe_env)
{
	int		status;
	char	**av;

	status = 0;
	av = ast_construct_cmd_args(sc);
	pipe_env->sc = sc;
	status = cmd_search_and_run(av, pipe_env);
	ft_strarrdel(av);
	return (status);
}

static int	eval_command(t_ast_command *command, t_pipe_env *pipe_env)
{
	return (eval_simple_command(command->simple_command, pipe_env));
}

static void	set_pipe(t_pipe *pipe, int rd, int wr)
{
	pipe->rd = rd;
	pipe->wr = wr;
}

int	eval_pipe_sequence(t_ast_pipe_sequence *ps)
{
	int			status;
	t_pipe_env	pipe_env;
	int			pipe_fd[2];

	pipe_env.sc = NULL;
	set_pipe(&(pipe_env.input), -1, -1);
	set_pipe(&(pipe_env.output), -1, -1);
	while (ps)
	{
		if (ps->pipe_sequence)
		{
			if (pipe(pipe_fd) == -1)
				return (return_perror(EPIPE, NULL));
			set_pipe(&(pipe_env.output), 1, pipe_fd[1]);
			status = eval_command(ps->command, &pipe_env);
			if (pipe_env.input.rd != -1)
				close(pipe_env.input.rd);
			close(pipe_fd[1]);
			set_pipe(&(pipe_env.output), -1, -1);
			set_pipe(&(pipe_env.input), pipe_fd[0], 0);
		}
		else
		{
			status = eval_command(ps->command, &pipe_env);
			if (pipe_env.input.rd != -1)
				close(pipe_env.input.rd);
			set_pipe(&(pipe_env.input), -1, -1);
		}
		ps = ps->pipe_sequence;
	}
	return (status);
}

int	eval_pipeline(t_ast_pipeline *pipeline)
{
	int			status;

	status = 0;
	if (pipeline->pipe_sequence)
		status = eval_pipe_sequence(pipeline->pipe_sequence);
	if (pipeline->bang == '!')
		status = ~status;
	return (status);
}

int	eval_and_or(t_ast_and_or *and_or)
{
	int	status;

	status = 0;
	if (and_or->pipeline)
		status = eval_pipeline(and_or->pipeline);
	if (and_or->and_or)
	{
		if ((and_or->op == AND_IF && !status)
				|| (and_or->op == OR_IF && status))
			status = eval_and_or(and_or->and_or);
	}
	return (status);
}

int	eval_list(t_ast_list *list)
{
	int				status;
	unsigned char	async;

	status = 0;
	async = 0;
	if (list->and_or)
	{
		if (list->separator_op && list->separator_op->c == '&')
			async = 1;
		status = eval_and_or(list->and_or);
	}
	if (list->list)
		status = eval_list(list->list);
	return (status);
}

int	eval_complete_command(t_ast_complete_command *cc)
{
	int	status;
	unsigned char	async;
	
	status = 0;
	async = 0;
	if (cc->list)
	{
		if (cc->separator_op && cc->separator_op->c == '&')
			async = 1;
		status = eval_list(cc->list);
	}
	return (status);
}

int	eval_complete_commands(t_ast_complete_commands *cc)
{
	int	status;

	status = 0;
	if (cc->complete_command)
		status = eval_complete_command(cc->complete_command);
	if (cc->complete_commands)
		status = eval_complete_commands(cc->complete_commands);
	return (status);
}

int	eval_program(t_ast_program *program)
{
	if (program->complete_commands)
		return (eval_complete_commands(program->complete_commands));
	return (0);
}
