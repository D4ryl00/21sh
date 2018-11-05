/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 12:35:00 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"
#include "jobcontrol.h"

/*
** Execute the command in a fork and execve.
*/

int			run(char *path, char **av, int async, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if ((pid = newjob(&status, async)) == -1)
		return (-1);
	if (!pid)
	{
		execve(path, av, env);
		return (-1);
	}
	return (WEXITSTATUS(status));
}
