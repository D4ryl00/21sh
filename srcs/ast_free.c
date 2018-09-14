/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 00:06:28 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/14 16:39:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdlib.h>

void	free_ast_io_file(t_ast_io_file *file)
{
	(void)file;
}

void	free_ast_io_redirect(t_ast_io_redirect *redirect)
{
	(void)redirect;
}

void	free_ast_cmd_suffix(t_ast_cmd_suffix * suffix)
{
	(void)suffix;
}

void	free_ast_simple_command(t_ast_simple_command *sc)
{
	(void)sc;
}

void	free_ast_command(t_ast_command *command)
{
	(void)command;
}

void	free_ast_program(t_ast_program *program)
{
	if (program)
	{
		if (program->command)
			free_ast_command(program->command);
		free(program);
	}
}
