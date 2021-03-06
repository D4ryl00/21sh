/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:52:27 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/05 16:22:06 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int	eval_list(t_ast_list *list, int async)
{
	int	status;

	status = 0;
	if (list->and_or)
	{
		if (list->separator_op && list->separator_op->c == '&')
			async = 1;
		status = eval_and_or(list->and_or, async);
	}
	if (list->list)
		status = eval_list(list->list, async);
	return (status);
}
