/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:45:26 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 13:05:57 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_complete_command(t_ast_complete_command *cc, struct s_job *job)
{
	int	status;

	status = 0;
	if (cc->list)
	{
		if (cc->separator_op && cc->separator_op->c == '&')
			job->async = 1;
		status = eval_list(cc->list, job);
	}
	return (status);
}

