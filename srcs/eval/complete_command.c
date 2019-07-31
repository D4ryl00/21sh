/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:45:26 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:15:07 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_complete_command(t_ast_complete_command *cc)
{
	int				status;

	status = 0;
	if (cc->list)
	{
		init_job_struct();
		if (cc->separator_op && cc->separator_op->c == '&')
			g_jobctrl.job.async = 1;
		status = eval_list(cc->list);
	}
	return (status);
}
