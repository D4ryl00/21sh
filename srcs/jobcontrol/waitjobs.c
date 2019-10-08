/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:09:15 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/07 16:04:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <sys/wait.h>

static int	process_select(t_list *node, void *data)
{
	struct s_process	*process;
	int					*pid;

	process = (struct s_process *)node->content;
	pid = data;
	if (process->pid == *pid)
		return (1);
	return (0);
}

/*
** Find a process by its id. If it's found, set jobp to the job ans return
** the process address.
*/

static struct s_process	*process_find(int pid, struct s_job **jobp)
{
	t_list			*job_node;
	struct s_job	*job;
	t_list			*process;

	if (!g_jobctrl.jobs)
		return (NULL);
	job_node = g_jobctrl.jobs;
	while (job_node)
	{
		job = (struct s_job *)job_node->content;
		if ((process = ft_lstselect(job->processes, &pid, &process_select)))
		{
			*jobp = job;
			return ((struct s_process *)process->content);
		}
		job_node = job_node->next;
	}
	return (NULL);
}



static int	update_status_process(pid_t pid, int status)
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
	{
		process->stopped = 1;
		if (!job->id)
			job->id = g_jobctrl.start_id++;
		print_job_infos(job, "stopped");
		if (tcgetattr(0, &job->tmodes) < 0)
			ft_dprintf(2, "stop_job: tcsetpgrp error\n");
	}
	else
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
	return (0);
}

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

void		update_all_status_process(void)
{
	int				status;
	pid_t			pid;

	while ((pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0)
	{
		update_status_process(pid, status);
	}
	/*if (pid == -1 && g_jobctrl.jobs)
	{
		ft_dprintf(2, "waitpid: error\n");
	}*/
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

int		get_job_status(struct s_job *job)
{
	t_list				*node_process;
	struct s_process	*process;

	node_process = job->processes;
	while (node_process->next)
		node_process = node_process->next;
	process = (struct s_process *)node_process->content;
	return (process->status);
}

int		waitjob(struct s_job *job)
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
			/*ft_lstdelif(&g_jobctrl.jobs, job,
					&test_job_node, &del_job_node);
			g_jobctrl.current_job = NULL;*/
			break ;
		}
	}
	return (status);
}

