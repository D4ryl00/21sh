/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:26:50 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/18 23:54:23 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exit
*/

#include <stdlib.h>

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "builtins.h"

char	*g_builtin_cmd[] =
{
	"echo",
	"env",
	"setenv",
	"unsetenv",
	"exit",
	""
};

int		is_builtin_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_builtin_cmd) >= 0)
		return (1);
	return (0);
}

int		run_builtin_cmd(char **av)
{
	int	status;

	status = 0;
	if (!g_jobctrl.current_job->forked
			|| (g_jobctrl.current_job->forked && g_jobctrl.current_job->child))
	{
		if (!ft_strcmp(av[0], "echo"))
			status = builtin_echo(av);
		else if (!ft_strcmp(av[0], "env"))
			status = builtin_env(av);
		else if (!ft_strcmp(av[0], "setenv"))
			status = builtin_setenv(&g_env, av);
		else if (!ft_strcmp(av[0], "unsetenv"))
			status = builtin_unsetenv(&g_env, av);
		else if (!ft_strcmp(av[0], "exit"))
			builtin_exit(av);
		if (g_jobctrl.current_job->child)
			exit(status);
	}
	else if (!g_jobctrl.current_job->nowait && !g_jobctrl.current_job->async)
		status = waitjob(g_jobctrl.current_job);
	return (status);
}
