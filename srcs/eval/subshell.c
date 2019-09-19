/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:24:30 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/19 15:12:21 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

void	get_subshell_cmd_name(t_ast_subshell *subshell,
		t_buf *subshell_cmd_name)
{
	(void)subshell;
	(void)subshell_cmd_name;
}

int	eval_subshell(t_ast_subshell *subshell)
{
	int	status;

	(void)subshell;
	status = 0;
	return (status);
}
