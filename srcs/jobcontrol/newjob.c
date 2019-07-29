/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newjob.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:17:08 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 10:26:28 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "jobcontrol.h"
#include <unistd.h>
#include <sys/wait.h>

pid_t	newjob(int *status, const unsigned char async)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
		return_perror(EFORK, NULL);
	if (!ft_lstpush(&g_asyncjobs, &pid, sizeof(pid_t)))
	{
		if (!pid)
			exit(1);
		return (-1);
	}
	if (pid && !async)
		waitpid(pid, status, 0);
	return (pid);
}
