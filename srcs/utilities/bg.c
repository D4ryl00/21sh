/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:34:02 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/16 10:58:32 by amordret         ###   ########.fr       */
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

int					utility_bg(char **av)
{
	struct s_job	*job;
	unsigned int	requested_job;

	requested_job = job_get_arg(av);
	job = job_find(g_jobctrl.jobs, requested_job);
	if (!job)
	{
		ft_dprintf(2, "bg: %s: no such job\n", av[1] ? av[1] : "current");
		return (1);
	}
	killpg(job->pgid, SIGCONT);
	return (0);
}
