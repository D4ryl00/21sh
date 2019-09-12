/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_list_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:45:00 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/12 07:37:21 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free
*/

#include <stdlib.h>

#include "libft.h"
#include "jobcontrol.h"

void	del_process_node(void *content, size_t content_size)
{
	(void)content_size;
	if (content)
		free(content);
}

void	del_job_node(void *content, size_t content_size)
{
	struct s_job	*job;

	(void)content_size;
	if (content)
	{
		job = (struct s_job *)content;
		if (job->cmd)
			free(job->cmd);
		ft_lstdel(&job->processes, del_process_node);
		free(content);
	}
}

int		test_job_node(t_list *node, void *data)
{
	if ((void *)node == data)
		return (1);
	return (0);
}
