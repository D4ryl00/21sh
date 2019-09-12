/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:12:50 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/12 07:39:28 by rbarbero         ###   ########.fr       */
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
	g_jobctrl.current_job->id = g_jobctrl.start_id++;
	killpg(g_jobctrl.current_job->pgid, SIGTSTP);
	print_job_infos(g_jobctrl.current_job, "stopped");
	g_jobctrl.current_job = NULL;
}
