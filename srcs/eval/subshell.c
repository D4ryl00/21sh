/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:24:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/12/19 13:49:36 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "jobcontrol.h"

int	eval_subshell(t_ast_subshell *subshell, t_job *job, int fork)
{
	int	status;

	(void)subshell;
	(void)job;
	(void)fork;
	status = 0;
	return (status);
}
