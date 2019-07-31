/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 12:42:00 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <unistd.h>
#include <sys/wait.h>

int			newjob(struct s_job *job, int force_async)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	job->pid = pid;
	if (!pid)
		job->forked = 1;
	if (!pid && force_async)
		job->async = 1;
	if (pid)
	{
		job->pgid = job->pgid == -1 ? pid : job->pgid;
		if (setpgid(pid, job->pgid) == -1)
			return_perror(ESETPGID, NULL);
	}
	if (job->pid && job->async && !force_async)
	{
		job->job_id = g_jobctrl.starting_job_id++;
		if (!ft_lstpushback(&g_jobctrl.asyncjobs, job, sizeof(*job)))
		{
			ft_perror(ENOMEM, NULL, 0);
			if (!pid)
				exit(1);
			return (-1);
		}
		ft_dprintf(2, "[%d] %d\n", job->job_id, pid);
	}
	return (0);
}
