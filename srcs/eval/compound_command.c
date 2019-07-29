/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:12:42 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 11:06:50 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

int	eval_compound_command(t_ast_compound_command *cc, struct s_job *job)
{
	int	status;

	status = 0;
	if (cc->subshell)
		status = eval_subshell(cc->subshell, job);
	return (status);
}
