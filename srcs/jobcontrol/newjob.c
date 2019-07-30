/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/30 13:36:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <unistd.h>
#include <sys/wait.h>

int	newjob(struct s_job *job, int force_async)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	job->pid = pid;
	if (!pid)
		job->forked = 1;
	if (!pid && force_async)
		job->async = 1;
	if (job->pid && job->async && !force_async
			&& !ft_lstpush(&g_asyncjobs, job, sizeof(struct s_job)))
	{
		ft_perror(ENOMEM, NULL, 0);
		if (!pid)
			exit(1);
		return (-1);
	}
	if (pid)
	{
		job->pgid = job->pgid == -1 ? pid : job->pgid;
		if (setpgid(pid, job->pgid) == -1)
			return_perror(ESETPGID, NULL);
	}
	/*if (job->pid && !async)
		waitpid(pid, status, 0);*/
	return (0);
}
