/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:52:27 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/30 22:25:03 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_list(t_ast_list *list, struct s_job *job)
{
	int				status;

	status = 0;
	if (list->and_or)
	{
		if (list->separator_op && list->separator_op->c == '&')
			job->async = 1;
		status = eval_and_or(list->and_or, job);
	}
	if (list->list)
	{
		init_job_struct(job);
		status = eval_list(list->list, job);
	}
	return (status);
}
