/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:12:42 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 11:27:26 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

int	eval_compound_command(t_ast_compound_command *cc, int async)
{
	int	status;

	status = 0;
	if (cc->subshell)
		status = eval_subshell(cc->subshell, async);
	return (status);
}