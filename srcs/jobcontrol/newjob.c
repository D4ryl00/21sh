/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 15:52:57 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <unistd.h>
#include <sys/wait.h>

pid_t	newjob(int *status, const unsigned char async)
{
	t_list	**jobs;
	pid_t	pid;

	if (async)
		jobs = &g_asyncjobs;
	else
		jobs = &g_syncjobs;
	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	if (!ft_lstpush(jobs, &pid, sizeof(pid_t)))
	{
		if (!pid)
			exit(1);
		return (-1);
	}
	if (pid && !async)
		waitpid(pid, status, 0);
	return (pid);
}
