/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:52:27 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:17:27 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_list(t_ast_list *list)
{
	int				status;

	status = 0;
	if (list->and_or)
	{
		if (list->separator_op && list->separator_op->c == '&')
			g_jobctrl.job.async = 1;
		status = eval_and_or(list->and_or);
	}
	if (list->list)
	{
		init_job_struct();
		status = eval_list(list->list);
	}
	return (status);
}
