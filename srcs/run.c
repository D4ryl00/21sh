/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/19 18:52:28 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char	*g_builtin_cmd[] =
{
	"exit",
	""
};

char	*g_special_builtin_cmd[] =
{
	"alloc",
	""
};

char	*g_utility_cmd[] =
{
	"alias",
	""
};

int	is_builtin_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_builtin_cmd) >= 0)
		return (1);
	return (0);
}

int	is_special_builtin_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_special_builtin_cmd) >= 0)
		return (1);
	return (0);
}

int	is_utility_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_utility_cmd) >= 0)
		return (1);
	return (0);
}
int	run_builtin_cmd(char **av)
{
	if (!ft_strcmp(av[0], "exit"))
		termcaps_reset_term_and_exit();
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

int	run_direct_path(char **av, t_ast_simple_command *sc)
{
	int	status;

	status = 127;
	if (!access(av[0], F_OK))
	{
		status = 126;
		if (!access(av[0], X_OK))
			status = run(av[0], av, sc);
		else
			ft_perror(EACCES, av[0]);
	}
	else
		ft_perror(ENOCMD, av[0]);
	return (status);
}

int	cmd_search_and_run(char ** av, t_ast_simple_command *sc)
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
			run_cmd_path(av, sc);
	}
	else
		run_direct_path(av, sc);
	return (0);
}

int	run(char *path, char **av, t_ast_simple_command *sc)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		ret;

	if ((pid = fork()) > 0)
	{
		ret = wait(&status);
		ft_set_term();
		ft_strarrdel(av);
		if (ret == -1)
			return (return_perror(EWAIT, NULL));
		return (WEXITSTATUS(status));
	}
	else if (!pid)
	{
		if (!(env = ft_lsttoarrstr(g_env)))
			exit_perror(ENOMEM, NULL);
		termcaps_reset_term();
		cmd_ast_eval_redirs(sc);
		execve(path, av, env);
		return (0);
	}
	else
		return (return_perror(EFORK, NULL));
}
