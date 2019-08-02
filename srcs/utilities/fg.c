/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:34:02 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/02 14:38:11 by rbarbero         ###   ########.fr       */
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
	struct s_job	*stopped;

	(void)av;
	node = g_jobctrl.asyncjobs;
	stopped = NULL;
	while (node)
	{
		if (((struct s_job *)node->content)->stopped)
			stopped = node->content;
		node = node->next;
	}
	if (stopped)
	{
		ft_memcpy(&g_jobctrl.job, stopped, sizeof(struct s_job));
		ft_lstdelif(&g_jobctrl.asyncjobs, &stopped->job_id,
				&test_job_node, &del_job_node);
		termcaps_reset_term();
		if (tcsetpgrp(g_termcaps.fd, g_jobctrl.job.pgid) == -1)
			return_perror(EOTHER, "eval_pipe_sequence: tcsetpgrp error");
		killpg(g_jobctrl.job.pgid, SIGCONT);
		waitjob();
	}
	return (0);
}
