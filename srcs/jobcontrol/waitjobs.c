/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:09:15 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/30 14:21:31 by rbarbero         ###   ########.fr       */
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

/*static int	is_finished(t_list *node, void *content)
{
	(void)node;
	(void)content;
	//if (waitpid((pid_t *)node->content, status, WNOHANG) == 0
}*/

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

void	waitjobs(t_list **jobs)
{
	t_list	**prev;
	t_list	*node;
	t_list	**list;
	int		status;

	status = 0;
	list = jobs ? jobs : &g_asyncjobs;
	prev = list;
	node = *list;
	while (*list)
	{
		if (waitpid(((struct s_job *)node->content)->pid, &status, WNOHANG) > 0)
		{
			ft_lstdelnode(prev, node, del_job_node);
			if (*prev)
				node = (*prev)->next;
		}
		else
		{
			prev = &node;
			node = node->next;
		}
		if (!node)
		{
			prev = list;
			node = *list;
		}
	}
}
