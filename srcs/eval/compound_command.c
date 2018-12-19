/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:12:42 by rbarbero          #+#    #+#             */
/*   Updated: 2018/12/19 13:47:52 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "jobcontrol.h"

int	eval_compound_command(t_ast_compound_command *cc, t_job *job, int fork)
{
	int	status;

	status = 0;
	if (cc->subshell)
		status = eval_subshell(cc->subshell, job, fork);
	return (status);
}
