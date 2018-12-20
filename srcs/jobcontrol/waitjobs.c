/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:09:15 by rbarbero          #+#    #+#             */
/*   Updated: 2018/12/20 14:35:24 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <sys/wait.h>

/*static void	del_pid(void *content, size_t content_size)
{
	(void)content_size;
	if (content)
		free(content);
}*/

/*static int	is_finished(t_list *node, void *content)
{
	(void)node;
	(void)content;
	//if (waitpid((pid_t *)node->content, status, WNOHANG) == 0
}*/

void	waitjobs(void)
{
	t_list	**prev;
	t_list	*node;
	int		status;

	status = 0;
	prev = &g_asyncjobs;
	node = g_asyncjobs;
	while (node)
	{
		if (!waitpid(*(pid_t *)node->content, &status, WNOHANG))
		{
			if (g_asyncjobs == node)
				g_asyncjobs = g_asyncjobs->next;
			ft_lstdelnode(prev, node, del_pid);
		}
		else
		{
			prev = &node;
			node = node->next;
		}
	}
}
