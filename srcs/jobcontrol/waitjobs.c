/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:09:15 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/10 16:30:26 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** waitpid
*/

#include <sys/wait.h>

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"

int			job_is_stopped(struct s_job *job)
{
	t_list				*process_node;
	struct s_process	*process;

	process_node = job->processes;
	while (process_node)
	{
		process = (struct s_process *)process_node->content;
		if (!process->completed && !process->stopped)
			return (0);
		process_node = process_node->next;
	}
	return (1);
}

int			job_is_completed(struct s_job *job)
{
	t_list				*process_node;
	struct s_process	*process;

	process_node = job->processes;
	while (process_node)
	{
		process = (struct s_process *)process_node->content;
		if (!process->completed)
			return (0);
		process_node = process_node->next;
	}
	return (1);
}

void		do_job_notification(void)
{
	t_list			*job_node;
	t_list			*next_node;
	struct s_job	*job;

	update_all_status_process();
	job_node = g_jobctrl.jobs;
	while (job_node)
	{
		next_node = job_node->next;
		job = (struct s_job *)job_node->content;
		if (job_is_completed(job))
		{
			if (job->async && !job->notified)
			{
				print_job_infos(job, "Done");
				job->notified = 1;
			}
			ft_lstdelif(&g_jobctrl.jobs, job_node,
					&test_job_node, &del_job_node);
		}
		job_node = next_node;
	}
}

static int	get_job_status(struct s_job *job)
{
	t_list				*node_process;
	struct s_process	*process;

	node_process = job->processes;
	while (node_process->next)
		node_process = node_process->next;
	process = (struct s_process *)node_process->content;
	return (process->status);
}

int			waitjob(struct s_job *job)
{
	int		status;
	pid_t	pid;

	status = 0;
	while ((pid = waitpid(-1, &status, WUNTRACED)) > 0)
	{
		update_status_process(pid, status);
		if (job_is_completed(job) || job_is_stopped(job))
		{
			status = get_job_status(job);
			break ;
		}
	}
	return (status);
}
