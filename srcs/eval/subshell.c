/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:24:30 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 11:27:57 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

int	eval_subshell(t_ast_subshell *subshell, int async)
{
	int	status;

	(void)subshell;
	(void)async;
	status = 0;
	return (status);
}
