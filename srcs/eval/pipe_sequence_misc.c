/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence_misc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:55:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/10 16:01:56 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipe, dup, dup2
*/

#include <unistd.h>

#include "eval.h"

void	set_pipe_struct(t_pipe *pipe, int rd, int wr)
{
	pipe->rd = rd;
	pipe->wr = wr;
}

/*
**	Get fd of an opened pipe and dup them on stdin or stdout.
*/

int		duplicate_fd(t_pipe_env *pipe_env)
{
	if ((pipe_env->input.rd != -1)
			&& (dup2(pipe_env->input.rd, pipe_env->input.wr) == -1))
		return (return_perror(EDUP, NULL, -1));
	if ((pipe_env->output.rd != -1)
			&& (dup2(pipe_env->output.wr, pipe_env->output.rd) == -1))
		return (return_perror(EDUP, NULL, -1));
	return (0);
}
