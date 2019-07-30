/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:09:15 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/30 16:39:07 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <sys/wait.h>

static void	del_job_node(void *content, size_t content_size)
{
	(void)content_size;
	if (content)
		free(content);
}

int		waitjob(struct s_job *job)
{
	int	status;

	if (job->async)
		waitpid(-job->pgid, &status, WNOHANG);
	else
		while (waitpid(-job->pgid, &status, 0) != -1)
			;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	waitjobs(void)
{
	t_list	**prev;
	t_list	*node;
	pid_t	pid;
	int		status;

	status = 0;
	prev = &g_asyncjobs;
	node = g_asyncjobs;
	while (node)
	{
		while ((pid = waitpid(-((struct s_job *)node->content)->pgid, &status,
						WNOHANG)) > 0)
		{
			ft_dprintf(2, "[%d] done\n", ((struct s_job *)node->content)->job_id);
			ft_lstdelnode(prev, node, del_job_node);
			if (*prev)
				node = (*prev)->next;
		}
		if (node)
		{
			prev = &node;
			node = node->next;
		}
	}
}
