/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:37:49 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/18 18:54:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

static int	run_simple_command(t_ast_simple_command *sc)
{
	t_ast_io_redirect	*input;
	t_ast_io_redirect	*output;

	input = NULL;
	output = NULL;
	//cmd_ast_get_redirs(&input, &output, sc);
	return (cmd_search_and_run(ast_construct_cmd_args(sc)));
}

static int	run_command(t_ast_command *command)
{
	return (run_simple_command(command->simple_command));
}

int	run_program(t_ast_program *program)
{
	return (run_command(program->command));
}
