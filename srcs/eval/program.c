/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:41:31 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 13:05:02 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "parser.h"
#include "jobcontrol.h"

int			eval_program(t_ast_program *program)
{
	struct s_job	job;

	init_job_struct(&job);
	if (program->complete_commands)
		return (eval_complete_commands(program->complete_commands, &job));
	return (0);
}
