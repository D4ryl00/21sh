/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/30 16:35:59 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <unistd.h>
#include <sys/wait.h>

static int	get_job_id(void)
{
	t_list	*node;
	int		id;

	id = 0;
	node = g_asyncjobs;
	while (node)
	{
		if (id < ((struct s_job *)node->content)->job_id)
			break ;
		id++;
		node = node->next;
	}
	return (id);
}

static int	cmp_asyncjobs(t_list *n1, t_list *n2)
{
	if (!n1 && !n2)
		return (0);
	if (!n1)
		return (-1);
	if (!n2)
		return (1);
	return (((struct s_job *)n1->content)->job_id
			- ((struct s_job *)n2->content)->job_id);
}

int			newjob(struct s_job *job, int force_async)
{
	pid_t	pid;
	t_list	*node;

	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	job->pid = pid;
	if (!pid)
		job->forked = 1;
	if (!pid && force_async)
		job->async = 1;
	if (pid)
	{
		job->job_id = get_job_id();
		job->pgid = job->pgid == -1 ? pid : job->pgid;
		if (setpgid(pid, job->pgid) == -1)
			return_perror(ESETPGID, NULL);
	}
	if (job->pid && job->async && !force_async)
	{
		if (!(node = ft_lstnew(job, sizeof(*job))))
		{
			ft_perror(ENOMEM, NULL, 0);
			if (!pid)
				exit(1);
			return (-1);
		}
		else
			ft_lstsortedinsert(&g_asyncjobs, node, &cmp_asyncjobs);
		ft_dprintf(2, "[%d] %d\n", job->job_id, pid);
	}
	return (0);
}
