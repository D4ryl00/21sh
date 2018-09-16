/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:45:25 by rbarbero          #+#    #+#             */
/*   Updated: 2018/09/17 01:02:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include <stdlib.h>

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
int		run_cmd_path(char **av)
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
				status = run(path, av);
			else
				ft_perror(EACCES, av[0]);
			free(path);
		}
		else
			ft_perror(ENOCMD, av[0]);
		ft_strarrdel(dirs);
	}
	return (status);
}
