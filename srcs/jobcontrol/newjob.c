/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:14:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <unistd.h>
#include <sys/wait.h>

int			newjob(int force_async)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	g_jobctrl.job.pid = pid;
	if (!pid)
		g_jobctrl.job.forked = 1;
	if (!pid && force_async)
		g_jobctrl.job.async = 1;
	if (pid)
	{
		g_jobctrl.job.pgid = g_jobctrl.job.pgid == -1 ? pid
			: g_jobctrl.job.pgid;
		if (setpgid(pid, g_jobctrl.job.pgid) == -1)
			return_perror(ESETPGID, NULL);
	}
	if (g_jobctrl.job.pid && g_jobctrl.job.async && !force_async)
	{
		g_jobctrl.job.job_id = g_jobctrl.starting_job_id++;
		if (!ft_lstpushback(&g_jobctrl.asyncjobs, &g_jobctrl.job,
					sizeof(g_jobctrl.job)))
		{
			ft_perror(ENOMEM, NULL, 0);
			if (!pid)
				exit(1);
			return (-1);
		}
		ft_dprintf(2, "[%d] %d\n", g_jobctrl.job.job_id, pid);
	}
	return (0);
}
