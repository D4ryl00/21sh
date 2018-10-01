/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:37:49 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/01 16:48:36 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

static int	eval_simple_command(t_ast_simple_command *sc)
{
	return (cmd_search_and_run(ast_construct_cmd_args(sc), sc));
}

static int	eval_command(t_ast_command *command)
{
	return (eval_simple_command(command->simple_command));
}

int	eval_pipe_sequence(t_ast_pipe_sequence *ps)
{
	return (eval_command(ps->command));
}

int	eval_pipeline(t_ast_pipeline *pipeline)
{
	int	status;

	status = 0;
	if (pipeline->pipe_sequence)
		status = eval_pipe_sequence(pipeline->pipe_sequence);
	if (pipeline->bang == '!')
		status = ~status;
	return (status);
}

int	eval_and_or(t_ast_and_or *and_or)
{
	int	status;

	status = 0;
	if (and_or->pipeline)
		status = eval_pipeline(and_or->pipeline);
	if (and_or->and_or)
	{
		if ((and_or->op == AND_IF && !status)
				|| (and_or->op == OR_IF && status))
			status = eval_and_or(and_or->and_or);
	}
	return (status);
}

int	eval_list(t_ast_list *list)
{
	int				status;
	unsigned char	async;

	status = 0;
	async = 0;
	if (list->and_or)
	{
		if (list->separator_op && list->separator_op->c == '&')
			async = 1;
		status = eval_and_or(list->and_or);
	}
	if (list->list)
		status = eval_list(list->list);
	return (status);
}

int	eval_complete_command(t_ast_complete_command *cc)
{
	int	status;
	unsigned char	async;
	
	status = 0;
	async = 0;
	if (cc->list)
	{
		if (cc->separator_op && cc->separator_op->c == '&')
			async = 1;
		status = eval_list(cc->list);
	}
	return (status);
}

int	eval_complete_commands(t_ast_complete_commands *cc)
{
	int	status;

	status = 0;
	if (cc->complete_command)
		status = eval_complete_command(cc->complete_command);
	if (cc->complete_commands)
		status = eval_complete_commands(cc->complete_commands);
	return (status);
}

int	eval_program(t_ast_program *program)
{
	if (program->complete_commands)
		return (eval_complete_commands(program->complete_commands));
	return (0);
}
