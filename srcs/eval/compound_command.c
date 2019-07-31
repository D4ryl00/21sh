/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:12:42 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:08:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

int	eval_compound_command(t_ast_compound_command *cc)
{
	int	status;

	status = 0;
	if (cc->subshell)
		status = eval_subshell(cc->subshell);
	return (status);
}
