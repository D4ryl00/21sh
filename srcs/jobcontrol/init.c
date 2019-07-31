/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:27:12 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 12:18:54 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobcontrol.h"

/*
** Definition of global variables
*/

struct s_jobctrl	g_jobctrl = { NULL, 1 };

/*
** Initialization with default values of struct a s_job.
*/

void	init_job_struct(struct s_job *job)
{
	job->job_id = -1;
	job->pid = -1;
	job->pgid = -1;
	job->forked = 0;
	job->async = 0;
	job->status = 1;
}
