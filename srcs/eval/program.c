/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:41:31 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 16:45:46 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

static int	eval_and_or(t_ast_and_or *and_or, int wait)
{
	int	status;

	status = 0;
	if (and_or->pipeline)
		status = eval_pipeline(and_or->pipeline, wait);
	if (and_or->and_or)
	{
		if ((!ft_strcmp(and_or->op, "&&") && !status)
				|| (!ft_strcmp(and_or->op, "||") && status))
			status = eval_and_or(and_or->and_or, wait);
	}
	return (status);
}

static int	eval_list(t_ast_list *list, int wait)
{
	int				status;

	status = 0;
	if (list->and_or)
	{
		if (list->separator_op && list->separator_op->c == '&')
			wait = WNOHANG;
		status = eval_and_or(list->and_or, wait);
	}
	if (list->list)
		status = eval_list(list->list, wait);
	return (status);
}

static int	eval_complete_command(t_ast_complete_command *cc)
{
	int	status;
	int	wait;

	status = 0;
	wait = 0;
	if (cc->list)
	{
		if (cc->separator_op && cc->separator_op->c == '&')
			wait = WNOHANG;
		status = eval_list(cc->list, wait);
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
