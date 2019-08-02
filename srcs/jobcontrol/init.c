/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:27:12 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/02 11:38:10 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** getpid
*/

#include <sys/types.h>
#include <unistd.h>

#include "sh.h"
#include "libft.h"
#include "jobcontrol.h"

/*
** Definition of global variables
*/

struct s_shell		g_shell = { -1, -1 };

struct s_jobctrl	g_jobctrl = { .asyncjobs = NULL, .starting_job_id = 1 };

/*
** Initialization of a struct s_shell.
*/

void	init_s_shell(void)
{
	g_shell.pid = getpid();
	g_shell.pgid = g_shell.pid;
	if (setpgid(g_shell.pid, g_shell.pgid) == -1)
		return_perror(EOTHER, "setpgid error");
}

/*
** Initialization with default values of struct a s_job.
*/

void	init_job_struct(void)
{
	g_jobctrl.job.job_id = -1;
	g_jobctrl.job.pid = -1;
	g_jobctrl.job.pgid = -1;
	g_jobctrl.job.child = 0;
	g_jobctrl.job.forked = 0;
	g_jobctrl.job.async = 0;
	g_jobctrl.job.stopped = 0;
	g_jobctrl.job.completed = 0;
	g_jobctrl.job.status = 1;
}
