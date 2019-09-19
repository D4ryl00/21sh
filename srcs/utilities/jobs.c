/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:46:54 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/19 21:29:11 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobcontrol.h"
#include "libft.h"

int	utility_jobs(char **av)
{
	t_list			*job_node;
	struct s_job	*job;
	char			*status;

	(void)av;
	update_all_status_process();
	job_node = g_jobctrl.jobs;
	while (job_node)
	{
		job = (struct s_job *)job_node->content;
		if (job->id > 0)
		{
			status = NULL;
			if (job_is_completed(job))
			{
				job->notified = 1;
				status = "Done";
			}
			else if (job_is_stopped(job))
				status = "Stopped";
			print_job_infos(job, status);
		}
		job_node = job_node->next;
	}
	return (0);
}
