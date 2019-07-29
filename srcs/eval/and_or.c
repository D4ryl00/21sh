/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:55:30 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 13:06:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_and_or(t_ast_and_or *and_or, struct s_job *job)
{
	int	status;

	status = 0;
	if (and_or->pipeline)
		status = eval_pipeline(and_or->pipeline, job);
	if (and_or->and_or)
	{
		if ((and_or->op == AND_IF && !status)
				|| (and_or->op == OR_IF && status))
			status = eval_and_or(and_or->and_or, job);
	}
	return (status);
}
