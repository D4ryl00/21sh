/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:41:31 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 11:30:52 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

static int	eval_and_or(t_ast_and_or *and_or, int async)
{
	int	status;

	status = 0;
	if (and_or->pipeline)
		status = eval_pipeline(and_or->pipeline, async);
	if (and_or->and_or)
	{
		if ((and_or->op == AND_IF && !status)
				|| (and_or->op == OR_IF && status))
			status = eval_and_or(and_or->and_or, async);
	}
	return (status);
}

static int	eval_list(t_ast_list *list, int async)
{
	int				status;

	status = 0;
	if (list->and_or)
	{
		if (list->separator_op && list->separator_op->c == '&')
			async = 1;
		status = eval_and_or(list->and_or, async);
	}
	if (list->list)
		status = eval_list(list->list, async);
	return (status);
}

static int	eval_complete_command(t_ast_complete_command *cc)
{
	int	status;
	int	async;

	status = 0;
	async = 0;
	if (cc->list)
	{
		if (cc->separator_op && cc->separator_op->c == '&')
			async = 1;
		status = eval_list(cc->list, async);
	}
	return (status);
}

static int	eval_complete_commands(t_ast_complete_commands *cc)
{
	int	status;

	status = 0;
	if (cc->complete_command)
		status = eval_complete_command(cc->complete_command);
	if (cc->complete_commands)
		status = eval_complete_commands(cc->complete_commands);
	return (status);
}

int			eval_program(t_ast_program *program)
{
	if (program->complete_commands)
		return (eval_complete_commands(program->complete_commands));
	return (0);
}
