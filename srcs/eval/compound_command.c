/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:12:42 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/07 15:44:30 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

void	get_compound_command_cmd_name(t_ast_compound_command *cc,
		t_buf *cc_cmd_name)
{
	if (cc->subshell)
		get_subshell_cmd_name(cc->subshell, cc_cmd_name);
}

int		eval_compound_command(t_ast_compound_command *cc)
{
	int	status;

	status = 0;
	if (cc->subshell)
		status = eval_subshell(cc->subshell);
	return (status);
}
