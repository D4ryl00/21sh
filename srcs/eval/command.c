/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:52:24 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 11:14:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int			eval_command(t_ast_command *command, t_pipe_env *pipe_env)
{
	return (eval_simple_command(command->simple_command, pipe_env));
}
