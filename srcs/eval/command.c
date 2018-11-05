/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:52:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 11:27:05 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

int			eval_command(t_ast_command *command, int async)
{
	int	status;

	status = 0;
	if (command->simple_command)
		status = eval_simple_command(command->simple_command, async);
	if (!status && command->compound_command)
		status = eval_compound_command(command->compound_command, async);
	return (status);
}
