/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:55:30 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/19 15:27:10 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_and_or(t_ast_and_or *and_or, int async)
{
	int		status;
	t_buf	and_or_cmd_name;

	status = 0;
	if (and_or->pipeline)
	{
		g_jobctrl.current_job = newjob(async);
		if (ft_buf_init(&and_or_cmd_name) == -1)
			return_perror(ENOMEM, "eval_and_or");
		get_pipeline_cmd_name(and_or->pipeline, &and_or_cmd_name);
		if (!(g_jobctrl.current_job->cmd = ft_buf_flush(&and_or_cmd_name)))
			return_perror(ENOMEM, "eval_and_or");
		status = eval_pipeline(and_or->pipeline);
		ft_buf_destroy(&and_or_cmd_name);
	}
	if (and_or->and_or)
	{
		if ((and_or->op == AND_IF && !status)
				|| (and_or->op == OR_IF && status))
			status = eval_and_or(and_or->and_or, async);
	}
	return (status);
}
