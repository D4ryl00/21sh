/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:36:33 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 06:53:13 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"

/*
** For each dirs entry, test if the path 'dirs[i]/filename' exist
** and return the path.
*/

static char	*get_path_exec(char *filename, char **dirs)
{
	char	*path;
	int		i;

	i = -1;
	if (dirs)
	{
		while (dirs[++i])
		{
			if (ft_sprintf(&path, "%s/%s", dirs[i], filename) < 0)
				exit_perror(ENOMEM, NULL);
			if (!access(path, F_OK))
				return (path);
			free(path);
		}
	}
	return (NULL);
}

/*
** Find where is the command name in the PATH of the env
** and run the command.
*/

static int	run_cmd_path(char **av, t_pipe_env *pipe_env)
{
	char	**dirs;
	char	*path;
	t_list	*env_path;
	int		status;

	path = NULL;
	status = 127;
	if ((env_path = ft_lstselect(g_env, "PATH", env_select_key)))
	{
		dirs = ft_strsplit(p_to_equ_char(env_path->content) + 1, ':');
		if ((path = get_path_exec(av[0], dirs)))
		{
			status = 126;
			if (!access(path, X_OK))
				status = run(path, av, pipe_env);
			else
				ft_perror(EACCES, av[0], 0);
			free(path);
		}
		else
			ft_perror(ENOCMD, av[0], 0);
		ft_strarrdel(dirs);
	}
	return (status);
}

/*
** The command path is know, so we call it directly if we can.
*/

static int	run_cmd_direct_path(char **av, t_pipe_env *pipe_env)
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

/*
** Find the good category of the command and execute it.
*/

int			cmd_select_type(char **av, t_pipe_env *pipe_env)
{
	if (!ft_strchr(av[0], '/'))
	{
		if (is_builtin_cmd(av))
			return (run_builtin_cmd(av));
		else if (is_special_builtin_cmd(av))
			return (run_special_builtin_cmd(av));
		else if (is_utility_cmd(av))
			return (run_utility_cmd(av));
		else
			return (run_cmd_path(av, pipe_env));
	}
	else
		return (run_cmd_direct_path(av, pipe_env));
	return (-1);
}
