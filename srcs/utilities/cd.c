/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 07:13:07 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 13:23:30 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "utilities.h"
#include <unistd.h>

/*
** for PATH_MAX
*/

#include <limits.h>

static int	cd_reduce_curpath(char *path, t_cd_params *params)
{
	char	*pwd;
	char	*tmp;
	size_t	len;

	if (ft_strlen(params->dir) + 1 >= PATH_MAX)
		return (-1);
	if (!(pwd = getcwd(NULL, 0)))
		return (return_perror(ENOMEM, NULL, -1));
	len = ft_strlen(pwd);
	if (pwd[len - 1] != '/')
	{
		if (!(tmp = ft_strjoin(pwd, "/")))
		{
			free(pwd);
			return (return_perror(ENOMEM, NULL, -1));
		}
		free(pwd);
		pwd = tmp;
	}
	if (!ft_strncmp(pwd, path, len))
		ft_strmove(path, path + len);
	free(pwd);
	if (ft_strlen(path) + 1 >= PATH_MAX)
		return (-1);
	return (0);
}

static int	cd_stage3(char *curpath, t_cd_params *params, char *pwd)
{
	if (chdir(curpath) == -1)
	{
		if (pwd)
			free(pwd);
		free(curpath);
		return (1);
	}
	if (params->p && !(pwd = getcwd(NULL, 0)))
		ft_perror(ENOMEM, NULL, 0);
	set_oldpwd(&g_env);
	if (pwd)
	{
		set_pwd(&g_env, pwd);
		free(pwd);
	}
	free(curpath);
	return (0);
}

static int	cd_stage2_2(char **curpath, t_cd_params *params, char **pwd)
{
	if ((*curpath)[0] != '/' && cd_add_pwd(curpath) == -1)
	{
		free(*curpath);
		return (1);
	}
	if (cd_path_to_canonical(*curpath) == -1)
		return (1);
	if (!(*pwd = ft_strdup(*curpath)))
	{
		free(*curpath);
		return (return_perror(ENOMEM, NULL, 1));
	}
	if (ft_strlen(*curpath) + 1 >= PATH_MAX
			&& cd_reduce_curpath(*curpath, params) == -1)
	{
		ft_dprintf(2, "cd: file name too long: %s\n", *curpath);
		free(*pwd);
		free(*curpath);
		return (1);
	}
	return (0);
}

static int	cd_stage2(char *curpath, t_cd_params *params)
{
	char	*pwd;

	pwd = NULL;
	if (!(params->p) && cd_stage2_2(&curpath, params, &pwd) == 1)
		return (1);
	return (cd_stage3(curpath, params, pwd));
}

int			utility_cd(char **av)
{
	char		*curpath;
	t_cd_params	params;

	curpath = NULL;
	cd_init_params(&params);
	cd_get_params(&params, &(av[1]));
	if (params.dir && params.dir[0] == '-' && !params.dir[1])
		return (cd_hyphen());
	if (!params.dir && (!(params.dir = env_get_value("HOME"))
				|| !params.dir[0]))
		return (return_print("42sh: cd: HOME not set\n", 1));
	if (params.dir[0] != '/' && params.dir[0] != '.')
	{
		if (!(curpath = cd_select_cdpath(&params)))
			return (1);
	}
	else if (!(curpath = ft_strdup(params.dir)))
		return (return_perror(ENOMEM, NULL, 1));
	return (cd_stage2(curpath, &params));
}
