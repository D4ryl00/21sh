/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:06:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/12/20 14:22:13 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <sys/wait.h>

int	waitjob(t_job *job)
{
	int			status;
	t_list		*p;

	status = 0;
	if (job)
	{
		p = job->process;
		while (p)
		{
			waitpid(((t_process *)p->content)->pid, &status, 0);
			p = p->next;
		}
	}
	return (WEXITSTATUS(status));
}
