/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:45:26 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/05 16:21:49 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_complete_command(t_ast_complete_command *cc)
{
	int	status;
	int	async;

	status = 0;
	async = 0;
	if (cc->list)
	{
		if (cc->separator_op && cc->separator_op->c == '&')
			async = 1;
		status = eval_list(cc->list, async);
	}
	return (status);
}
