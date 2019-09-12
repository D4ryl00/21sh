/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/05 15:12:23 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include "signals.h"

struct s_job	*newjob(int async)
{
	struct s_job	job;
	t_list			*node;

	ft_memset(&job, 0, sizeof(job));
	job.async = async;
	if (async)
		job.id = g_jobctrl.start_id++;
	if (!(node = ft_lstpushback(&g_jobctrl.jobs, &job, sizeof(job))))
		exit_perror(ENOMEM, NULL);
	return ((struct s_job *)node->content);
}

int				newprocess(struct s_job *job)
{
	pid_t				pid;
	struct s_process	process;
	t_list				*node;

	ft_memset(&process, 0, sizeof(process));
	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	if (!pid)
	{
		process.pid = getpid();
		job->child = 1;
	}
	if (pid)
		process.pid = pid;
	if (!job->processes)
		job->pgid = process.pid;
	if (setpgid(process.pid, job->pgid) == -1)
		ft_perror(EOTHER, "setpgid error", 0);
	if (!(node = ft_lstpushback(&job->processes, &process, sizeof(process))))
		return_perror(ENOMEM, NULL);
	return (0);
}
