/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:12:50 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/17 10:36:16 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** killpg
*/

#include <signal.h>

#include "jobcontrol.h"
#include "libft.h"
#include "sh.h"
#include "signals.h"

void	stop_job(int signal)
{
	(void)signal;
	if (signal != SIGTSTP || !g_jobctrl.current_job->processes)
		return ;
	g_jobctrl.current_job->id = g_jobctrl.start_id++;
	//killpg(g_jobctrl.current_job->pgid, SIGTSTP);
	if (tcgetattr(0, &g_jobctrl.current_job->tmodes) < 0)
		ft_dprintf(2, "stop_job: tcsetpgrp error\n");
	print_job_infos(g_jobctrl.current_job, "stopped");
	g_jobctrl.current_job = NULL;
}
