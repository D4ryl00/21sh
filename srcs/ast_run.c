/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:37:49 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/16 01:43:45 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	run_simple_command(t_ast_simple_command *sc)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) > 0)
		return (wait(&status));
	else if (!pid)
		return (cmd_search(ast_get_cmd_name(sc), ast_construct_cmd_args(sc)));
	else
		return (return_perror(ENOFORK, NULL));
}

static int	run_command(t_ast_command *command)
{
	run_simple_command(command->simple_command);
	return (0);
}

int	run_program(t_ast_program *program)
{
	run_command(program->command);
	return (0);
}
