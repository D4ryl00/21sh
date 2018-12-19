/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/12/19 15:28:41 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"
#include "jobcontrol.h"
#include <unistd.h>

/*
** Execute the command in a fork and execve.
*/

int			run(char *path, char **av, char **env, t_job *job, int is_fork)
{
	t_process	process;

	if (!is_fork && (process.pid = fork()) == -1)
		return (-1);
	if (!process.pid)
	{
		execve(path, av, env);
		return (-1);
	}
	else
	{
		if (!ft_lstpushback(&(job->process), &process, sizeof(t_process)))
			return_perror(ENOMEM, NULL);
	}
	return (0);
}
