/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:34:02 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/01 12:39:16 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** killpg
*/

# include <signal.h>

#include "sh.h"
#include "jobcontrol.h"
#include "libft.h"

int	utility_fg(char **av)
{
	t_list			*node;
	struct s_job	*suspended;

	(void)av;
	node = g_jobctrl.asyncjobs;
	suspended = NULL;
	while (node)
	{
		if (((struct s_job *)node->content)->suspended)
			suspended = node->content;
		node = node->next;
	}
	if (suspended)
	{
		ft_memcpy(&g_jobctrl.job, suspended, sizeof(struct s_job));
		ft_lstdelif(&g_jobctrl.asyncjobs, &suspended->job_id,
				&test_job_node, &del_job_node);
		killpg(g_jobctrl.job.pgid, SIGCONT);
		termcaps_reset_term();
		tcsetpgrp(g_termcaps.fd, g_jobctrl.job.pgid);
	}
	return (0);
}
