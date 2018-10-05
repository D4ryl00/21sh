/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:50:04 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 09:51:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include <unistd.h>

static void	set_pipe(t_pipe *pipe, int rd, int wr)
{
	pipe->rd = rd;
	pipe->wr = wr;
}

int			eval_pipe_sequence(t_ast_pipe_sequence *ps)
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

