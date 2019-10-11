/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:13:25 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/10 16:14:37 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"

static int			process_select(t_list *node, void *data)
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

struct s_process	*process_find(int pid, struct s_job **jobp)
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

