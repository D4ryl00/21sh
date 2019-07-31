/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:27:12 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:26:52 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobcontrol.h"

/*
** Definition of global variables
*/

struct s_jobctrl	g_jobctrl = { .asyncjobs = NULL, .starting_job_id = 1 };

/*
** Initialization with default values of struct a s_job.
*/

void	init_job_struct(void)
{
	g_jobctrl.job.job_id = -1;
	g_jobctrl.job.pid = -1;
	g_jobctrl.job.pgid = -1;
	g_jobctrl.job.forked = 0;
	g_jobctrl.job.async = 0;
	g_jobctrl.job.status = 1;
}
