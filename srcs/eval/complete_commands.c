/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:39:46 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/30 11:16:33 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

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
