/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:52:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/07 15:44:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

void	get_command_cmd_name(t_ast_command *command, t_buf *command_cmd_name)
{
	if (command->simple_command)
		get_simple_command_cmd_name(command->simple_command, command_cmd_name);
	if (command->compound_command)
		get_compound_command_cmd_name(command->compound_command,
				command_cmd_name);
}

int		eval_command(t_ast_command *command)
{
	int	status;

	status = 0;
	if (command->simple_command)
		status = eval_simple_command(command->simple_command);
	if (!status && command->compound_command)
		status = eval_compound_command(command->compound_command);
	return (status);
}
