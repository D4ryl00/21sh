/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:09:15 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/01 10:46:57 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <sys/wait.h>

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
