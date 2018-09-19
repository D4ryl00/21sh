/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:37:49 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/19 02:30:01 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

static int	run_simple_command(t_ast_simple_command *sc)
{
	int		status;
	t_list	*backup;

	backup = cmd_ast_eval_redirs(sc);
	status = cmd_search_and_run(ast_construct_cmd_args(sc));
	cmd_ast_undo_redirs(backup);
	return (status);
}

static int	run_command(t_ast_command *command)
{
	return (run_simple_command(command->simple_command));
}

int	run_program(t_ast_program *program)
{
	return (run_command(program->command));
}
