/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:45:26 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/30 11:15:31 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_complete_command(t_ast_complete_command *cc)
{
	int				status;
	struct s_job	job;

	status = 0;
	if (cc->list)
	{
		init_job_struct(&job);
		if (cc->separator_op && cc->separator_op->c == '&')
			job.async = 1;
		status = eval_list(cc->list, &job);
	}
	return (status);
}
