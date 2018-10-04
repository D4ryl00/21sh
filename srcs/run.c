/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:48:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/04 10:35:11 by amordret         ###   ########.fr       */
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

int	run_direct_path(char **av, t_pipe_env *pipe_env)
{
	int	status;

	status = 127;
	if (!access(av[0], F_OK))
	{
		status = 126;
		if (!access(av[0], X_OK))
			status = run(av[0], av, pipe_env);
		else
			ft_perror(EACCES, av[0], 0);
	}
	else
		ft_perror(ENOCMD, av[0], 0);
	return (status);
}

int	cmd_search_and_run(char ** av, t_pipe_env *pipe_env)
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
			run_cmd_path(av, pipe_env);
	}
	else
		run_direct_path(av, pipe_env);
	return (0);
}

int	run(char *path, char **av, t_pipe_env *pipe_env)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		ret;

	if (!(pid = fork()))
	{
		if (!(env = ft_lsttoarrstr(g_env)))
			exit_perror(ENOMEM, NULL);
		if ((cmd_ast_eval_pipe(pipe_env) == -1)
				|| (cmd_ast_eval_redirs(pipe_env->sc) == -1))
			return (-1);
		termcaps_reset_term();
		execve(path, av, env);
		return (0);
	}
	else if (pid == -1)
		return (return_perror(EFORK, NULL));
	ret = wait(&status);
	ft_set_term();
	if (ret == -1)
		return (return_perror(EWAIT, NULL));
	return (WEXITSTATUS(status));
}
