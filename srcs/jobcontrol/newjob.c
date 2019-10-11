/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 12:04:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include "signals.h"

#include <stdio.h>

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

static void		set_process_values(pid_t pid, struct s_job *job,
		struct s_process *process)
{
	if (!pid)
	{
		process->pid = getpid();
		job->child = 1;
	}
	if (pid)
	{
		process->pid = pid;
		job->forked = 1;
	}
}

int				newprocess(struct s_job *job)
{
	pid_t				pid;
	struct s_process	process;
	t_list				*node;

	ft_memset(&process, 0, sizeof(process));
	if ((pid = fork()) == -1)
		return (return_perror(EFORK, NULL, -1));
	set_process_values(pid, job, &process);
	if (!job->processes)
		job->pgid = process.pid;
	if (setpgid(process.pid, job->pgid) == -1)
	{
		ft_perror(EOTHER, "setpgid error", 0);
		perror(NULL);
	}
	if (!job->async)
		tcsetpgrp(g_termcaps.fd, job->pgid);
	if (!(node = ft_lstpushback(&job->processes, &process, sizeof(process))))
		return (return_perror(ENOMEM, NULL, -1));
	return (0);
}
