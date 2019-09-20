/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:34:02 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/20 09:03:43 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** killpg
*/

# include <signal.h>

#include "sh.h"
#include "jobcontrol.h"
#include "libft.h"

static struct s_job	*find_bg_job(t_list *jobs, unsigned int job_id)
{
	t_list			*node;
	struct s_job	*current_job;
	struct s_job	*finded_job;

	node = jobs;
	finded_job = NULL;
	while (node)
	{
		current_job = (struct s_job *)node->content;
		if (!job_id)
		{
			if (current_job->id > 0 && (!finded_job
						|| (current_job->id > finded_job->id)))
				finded_job = current_job;
		}
		else
		{
			if (job_id == current_job->id)
			{
				finded_job = current_job;
				break ;
			}
		}
		node = node->next;
	}
	return (finded_job);
}

static int	get_arg_job(char **av)
{
	int	res;

	res = 0;
	if (av[1])
		res = ft_atoi(av[1]);
	return (res);
}

int	utility_bg(char **av)
{
	struct s_job	*job;
	unsigned int	requested_job;

	requested_job = get_arg_job(av);
	job = find_bg_job(g_jobctrl.jobs, requested_job);
	if (!job)
	{
		dprintf(2, "bg: %s: no such job\n", av[1] ? av[1] : "current");
		return (1);
	}
	killpg(job->pgid, SIGCONT);
	return (0);
}
