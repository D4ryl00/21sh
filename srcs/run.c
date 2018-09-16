/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/17 01:03:50 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	is_builtin_cmd(char **av)
{
	(void)av;
	return (0);
}

int	is_special_builtin_cmd(char **av)
{
	(void)av;
	return (0);
}

int	is_utility_cmd(char **av)
{
	(void)av;
	return (0);
}
int	run_builtin_cmd(char **av)
{
	(void)av;
	return (0);
}

int	run_special_builtin_cmd(char **av)
{
	(void)av;
	return (0);
}

int	run_utility_cmd(char **av)
{
	(void)av;
	return (0);
}

int	cmd_search_and_run(char **av)
{
	if (!ft_strchr(av[0], '/'))
	{
		if (is_builtin_cmd(av))
			run_builtin_cmd(av);
		else if (is_special_builtin_cmd(av))
			run_special_builtin_cmd(av);
		else if (is_utility_cmd(av))
			run_utility_cmd(av);
		else
			run_cmd_path(av);
	}
	/*if (!access(name, F_OK))
	{
		if (!access(name, X_OK))
		{
			execve(name, args, NULL);
			ft_strarrdel(args);
			args = NULL;
		}
		else
			return_perror(EACCES, name);
	}
	else
		return_perror(ENOCMD, name);*/
	return (0);
}

int	run(char *path, char **av)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		ret;

	if ((pid = fork()) > 0)
	{
		ret = wait(&status);
		ft_strarrdel(av);
		if (ret == -1)
			return (return_perror(EWAIT, NULL));
		return (WEXITSTATUS(status));
	}
	else if (!pid)
	{
		if (!(env = ft_lsttoarrstr(g_env)))
			exit_perror(ENOMEM, NULL);
		execve(path, av, env);
		return (0);
	}
	else
		return (return_perror(EFORK, NULL));
}
