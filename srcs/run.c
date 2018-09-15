/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/15 23:31:52 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	run_simple_command(t_ast_simple_command *sc)
{
	pid_t	pid;
	int		status;

	(void)sc;
	if ((pid = fork()) > 0)
		wait(&status);
	else if (!pid)
	{
	}
	else
		return_perror(ENOFORK, NULL);
	return (0);
}

int	run_command(t_ast_command *command)
{
	run_simple_command(command->simple_command);
	return (0);
}

int	run_program(t_ast_program *program)
{
	run_command(program->command);
	return (0);
}
