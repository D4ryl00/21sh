/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:52:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:08:34 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

int			eval_command(t_ast_command *command)
{
	int	status;

	status = 0;
	if (command->simple_command)
		status = eval_simple_command(command->simple_command);
	if (!status && command->compound_command)
		status = eval_compound_command(command->compound_command);
	return (status);
}
