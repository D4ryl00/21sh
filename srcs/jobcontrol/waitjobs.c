/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:09:15 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:12:33 by rbarbero         ###   ########.fr       */
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

static int	test_job_node(t_list *node, void *data)
{
	if (((struct s_job *)node->content)->pgid == *(pid_t *)data)
		return (1);
	return (0);
}

int		waitjob(void)
{
	int	status;

	if (g_jobctrl.job.async)
		waitpid(-g_jobctrl.job.pgid, &status, WNOHANG);
	else
		while (waitpid(-g_jobctrl.job.pgid, &status, 0) != -1)
			;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	waitjobs(int signal)
{
	t_list	*node;
	t_list	*next;
	pid_t	pid;

	(void)signal;
	node = g_jobctrl.asyncjobs;
	while (node)
	{
		while ((pid = waitpid(-((struct s_job *)node->content)->pgid,
					&((struct s_job *)node->content)->status, WNOHANG)) > 0)
			;
		if (pid == -1)
		{
			ft_dprintf(2, "[%d] done\n", ((struct s_job *)node->content)->job_id);
			next = node->next;
			ft_lstdelif(&g_jobctrl.asyncjobs,
					&((struct s_job *)node->content)->pgid,
					&test_job_node, &del_job_node);
			node = next;
		}
		else
			node = node->next;
	}
}
