/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:22:18 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/10 16:34:19 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** waitpid
*/

#include <sys/wait.h>

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"

static void	set_process_as_stopped(struct s_job *job, struct s_process *process)
{
	process->stopped = 1;
	if (!job->id)
		job->id = g_jobctrl.start_id++;
	print_job_infos(job, "stopped");
	if (tcgetattr(0, &job->tmodes) < 0)
		ft_dprintf(2, "stop_job: tcsetpgrp error\n");
}

static void	set_process_as_completed(struct s_process *process, int status)
{
	process->completed = 1;
	if (WIFSIGNALED(status))
	{
		ft_dprintf(2, "%d Terminated by signal %d.\n", process->pid,
				WTERMSIG(status));
	}
	else
		process->status = WEXITSTATUS(status);
}

int			update_status_process(pid_t pid, int status)
{
	struct s_job		*job;
	struct s_process	*process;

	if (!(process = process_find(pid, &job)))
	{
		ft_dprintf(2, "process %d not found\n", pid);
		return (-1);
	}
	process->status = status;
	if (WIFSTOPPED(status))
		set_process_as_stopped(job, process);
	else
		set_process_as_completed(process, status);
	return (0);
}

void		update_all_status_process(void)
{
	int		status;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0)
		update_status_process(pid, status);
}
