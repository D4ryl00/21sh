/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:46:54 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/17 23:01:51 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobcontrol.h"
#include "libft.h"

int	utility_jobs(char **av)
{
	t_list			*job_node;
	struct s_job	*job;

	(void)av;
	job_node = g_jobctrl.jobs;
	while (job_node)
	{
		job = (struct s_job *)job_node->content;
		if (job->id > 0)
			print_job_infos(job, NULL);
		job_node = job_node->next;
	}
	return (0);
}
