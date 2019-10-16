/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:34:02 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/16 10:58:39 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** killpg
*/

#include <signal.h>

#include "sh.h"
#include "libft.h"
#include "jobcontrol.h"
#include "utilities.h"

int	utility_fg(char **av)
{
	struct s_job	*job;
	unsigned int	requested_job;

	requested_job = job_get_arg(av);
	job = job_find(g_jobctrl.jobs, requested_job);
	if (!job)
	{
		ft_dprintf(2, "fg: %s: no such job\n", av[1] ? av[1] : "current");
		return (1);
	}
	g_jobctrl.current_job = job;
	g_jobctrl.current_job->id = 0;
	if (tcsetpgrp(g_termcaps.fd, g_jobctrl.current_job->pgid) == -1)
		return (return_perror(EOTHER, "fg: tcsetpgrp error", -1));
	killpg(g_jobctrl.current_job->pgid, SIGCONT);
	waitjob(g_jobctrl.current_job);
	return (0);
}
