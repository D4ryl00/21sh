/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 00:06:28 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/13 00:15:53 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdlib.h>

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
