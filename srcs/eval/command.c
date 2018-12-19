/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:52:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/12/19 13:45:08 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "jobcontrol.h"

int			eval_command(t_ast_command *command, t_job *job, int fork)
{
	int	status;

	status = 0;
	if (command->simple_command)
		status = eval_simple_command(command->simple_command, job, fork);
	if (!status && command->compound_command)
		status = eval_compound_command(command->compound_command, job, fork);
	return (status);
}
