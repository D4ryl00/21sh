/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 16:11:16 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"
#include "jobcontrol.h"

/*
** Execute the command in a fork and execve.
*/

int			run(char *path, char **av, char **env)
{
	int		status;

	status = 0;
	if (!g_jobctrl.job.forked && newjob(0) == -1)
		return (-1);
	if (!g_jobctrl.job.pid)
	{
		execve(path, av, env);
		return (-1);
	}
	status = waitjob();
	return (status);
}
