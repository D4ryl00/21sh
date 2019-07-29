/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:46:20 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 13:06:41 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_pipeline(t_ast_pipeline *pipeline, struct s_job *job)
{
	int	status;

	status = 0;
	if (pipeline->pipe_sequence)
		status = eval_pipe_sequence(pipeline->pipe_sequence, job);
	if (pipeline->bang == '!') //to modify with status changes
		status = ~status;
	return (status);
}
