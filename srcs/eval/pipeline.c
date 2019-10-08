/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:46:20 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/07 15:45:01 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

void	get_pipeline_cmd_name(t_ast_pipeline *pipeline,
		t_buf *pipeline_cmd_name)
{
	if (pipeline->pipe_sequence)
		get_pipe_sequence_cmd_name(pipeline->pipe_sequence, pipeline_cmd_name);
}

int		eval_pipeline(t_ast_pipeline *pipeline)
{
	int	status;

	status = 0;
	if (pipeline->pipe_sequence)
		status = eval_pipe_sequence(pipeline->pipe_sequence);
	if (pipeline->bang == '!')
		status = ~status;
	return (status);
}
