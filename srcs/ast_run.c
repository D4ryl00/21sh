/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:37:49 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/30 19:58:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

static int	run_simple_command(t_ast_simple_command *sc)
{
	return (cmd_search_and_run(ast_construct_cmd_args(sc), sc));
}

static int	run_command(t_ast_command *command)
{
	return (run_simple_command(command->simple_command));
}

int	run_pipe_sequence(t_ast_pipe_sequence *ps)
{
	return (run_command(ps->command));
}

int	run_pipeline(t_ast_pipeline *pipeline)
{
	return (run_pipe_sequence(pipeline->pipe_sequence));
}

int	run_and_or(t_ast_and_or *and_or)
{
	return (run_pipeline(and_or->pipeline));
}

int	run_list(t_ast_list *list)
{
	return (run_and_or(list->and_or));
}

int	run_complete_command(t_ast_complete_command *cc)
{
	return (run_list(cc->list));
}

int	run_complete_commands(t_ast_complete_commands *cc)
{
	return (run_complete_command(cc->complete_command));
}

int	run_program(t_ast_program *program)
{
	if (program)
		return (run_complete_commands(program->complete_commands));
	return (0);
}
