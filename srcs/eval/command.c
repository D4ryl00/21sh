/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:52:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 11:05:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

int			eval_command(t_ast_command *command, struct s_job *job)
{
	int	status;

	status = 0;
	if (command->simple_command)
		status = eval_simple_command(command->simple_command, job);
	if (!status && command->compound_command)
		status = eval_compound_command(command->compound_command, job);
	return (status);
}
