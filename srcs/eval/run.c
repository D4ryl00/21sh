/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/12 11:36:07 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"
#include "jobcontrol.h"
#include "signals.h"

/*
** Execute the command in a fork and execve.
*/

int			run(char *path, char **av, char **env)
{
	int		status;

	status = 0;
	if (!g_jobctrl.current_job->processes
			&& newprocess(g_jobctrl.current_job) == -1)
		return (-1);
	if (!g_jobctrl.current_job->child && !g_jobctrl.current_job->async)
	{
		ft_dprintf(2, "[%d] %d\n",
				((struct s_process *)g_jobctrl.jobs->content)->pid,
				g_jobctrl.current_job->id);
		tcsetpgrp(g_termcaps.fd, g_jobctrl.current_job->pgid);
	}
	if (g_jobctrl.current_job->child)
	{
		if (signals_restore() == -1)
			exit(1);
		execve(path, av, env);
		exit (1);
	}
	if (!g_jobctrl.current_job->async)
		waitjob(g_jobctrl.current_job);
	tcsetpgrp(g_termcaps.fd, g_shell.pgid);
	return (get_job_status(g_jobctrl.current_job));
}
