/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:24:30 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 13:21:20 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "jobcontrol.h"

int	eval_subshell(t_ast_subshell *subshell, struct s_job *job)
{
	int	status;

	(void)subshell;
	(void)job;
	status = 0;
	return (status);
}
