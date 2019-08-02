/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/02 14:25:19 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include "signals.h"

static int	init_child_foreground(void)
{
	if (g_jobctrl.job.pgid == -1)
		g_jobctrl.job.pgid = g_jobctrl.job.pid;
	setpgid(g_jobctrl.job.pid, g_jobctrl.job.pgid);
	if (g_jobctrl.job.async)
		tcsetpgrp(g_termcaps.fd, g_jobctrl.job.pgid);
	return (0);
}

int			newjob(int force_async)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	if (!pid)
	{
		g_jobctrl.job.pid = getpid();
		if (init_child_foreground() == -1) //not for async!!!
			exit(1);
		if (signals_restore() == -1)
			exit(1);
		g_jobctrl.job.child = 1;
		g_jobctrl.job.forked = 1;
		if (force_async)
			g_jobctrl.job.async = 1;
	}
	if (pid)
	{
		g_jobctrl.job.pid = pid;
		if (init_child_foreground() == -1)
			return (-1);
		if (g_jobctrl.job.async && !force_async)
		{
			g_jobctrl.job.job_id = g_jobctrl.starting_job_id++;
			if (!ft_lstpushback(&g_jobctrl.asyncjobs, &g_jobctrl.job,
						sizeof(g_jobctrl.job)))
				exit_perror(ENOMEM, NULL);
			ft_dprintf(2, "[%d] %d\n", g_jobctrl.job.job_id, pid);
		}
	}
	return (0);
}
