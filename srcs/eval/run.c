/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/20 01:13:41 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "eval.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
** Execute the command in a fork and execve.
*/

int			run(char *path, char **av)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		ret;

	if (!(pid = fork()))
	{
		if (!(env = ft_lsttoarrstr(g_env)))
			exit_perror(ENOMEM, NULL);
		execve(path, av, env);
		return (0);
	}
	else if (pid == -1)
		return (return_perror(EFORK, NULL));
	ret = wait(&status);
	if (ret == -1)
		return (return_perror(EWAIT, NULL));
	return (WEXITSTATUS(status));
}
