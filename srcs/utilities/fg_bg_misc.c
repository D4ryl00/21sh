/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:02:19 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/10 10:58:45 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobcontrol.h"
#include "libft.h"

static int			select_id_job(t_list *node, void *data)
{
	struct s_job	*job;

	job = (struct s_job *)node->content;
	if (job->id == *(unsigned int *)data)
		return (1);
	return (0);
}

static struct s_job	*find_last_bg_job(t_list *jobs)
{
	struct s_job	*job;
	struct s_job	*finded_job;

	finded_job = NULL;
	while (jobs)
	{
		job = (struct s_job *)jobs->content;
		if (job->id > 0 && (!finded_job || (job->id > finded_job->id)))
			finded_job = job;
		jobs = jobs->next;
	}
	return (finded_job);
}

struct s_job		*job_find(t_list *jobs, unsigned int job_id)
{
	t_list			*job_node;

	job_node = NULL;
	if (!job_id)
		return (find_last_bg_job(jobs));
	if ((job_node = ft_lstselect(jobs, &job_id, select_id_job)))
		return ((struct s_job *)job_node->content);
	return (NULL);
}

int					job_get_arg(char **av)
{
	int	res;

	res = 0;
	if (av[1])
		res = ft_atoi(av[1]);
	return (res);
}
