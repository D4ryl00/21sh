/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_to_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:12:50 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 20:19:27 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sigaction
*/

#include <signal.h>

#include "jobcontrol.h"
#include "libft.h"
#include "sh.h"

void	job_to_bg(int signal)
{
	(void)signal;
	g_jobctrl.job.suspended = 1;
	if (!ft_lstpushback(&g_jobctrl.asyncjobs, &g_jobctrl.job,
				sizeof(g_jobctrl.job)))
	{
		ft_perror(ENOMEM, NULL, 0);
		return ;
	}
}
