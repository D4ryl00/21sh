/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_to_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:12:50 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/02 14:12:12 by rbarbero         ###   ########.fr       */
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

void	job_to_bg(int signal)
{
	(void)signal;
	g_jobctrl.job.stopped = 1;
	g_jobctrl.job.job_id = g_jobctrl.starting_job_id++;
	if (!ft_lstpushback(&g_jobctrl.asyncjobs, &g_jobctrl.job,
				sizeof(g_jobctrl.job)))
	{
		ft_perror(ENOMEM, NULL, 0);
		return ;
	}
	killpg(g_jobctrl.job.pgid, SIGTSTP);
}
