/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 07:13:07 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/15 17:40:29 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "utilities.h"
#include <unistd.h>

static void	cd_init_params(t_cd_params *params)
{
	params->L = 0;
	params->P = 0;
	params->dir = NULL;
}

static void	cd_get_params(t_cd_params *params, char **av)
{
	while (*av)
	{
		if ((*av)[0] == '-' && (*av)[1] == 'L')
		{
			params->L = 1;
			params->P = 0;
		}
		else if ((*av)[0] == '-' && (*av)[1] == 'P')
		{
			params->L = 1;
			params->P = 0;
		}
		else
		{
			params->dir = (*av)[0] ? *av : NULL;
			break ;
		}
		av++;
	}
}

static char	*cd_test_cdpath(char *path, t_cd_params *params)
{
	char	*fullpath;
	size_t	size;

	fullpath = NULL;
	size = ft_strlen(path);
	if (path[size - 1] != '/')
		ft_sprintf(&fullpath, "%s/%s", path, params->dir);
	else
		fullpath = ft_strjoin(path, params->dir);
	if (!fullpath)
		exit_perror(ENOMEM, NULL);
	if (access(fullpath, F_OK) && access(fullpath, X_OK))
			return (fullpath);
	free(fullpath);
	return (NULL);
}

static char	*cd_select_cdpath(t_cd_params *params)
{
	char	*cdpath;
	char	**arrpaths;
	char	*path;
	int		i;

	path = NULL;
	if ((cdpath = get_env_value("CDPATH")) && cdpath[0])
	{
		if (!(arrpaths = ft_strsplit(cdpath, ':')))
			exit_perror(ENOMEM, NULL);
		i = -1;
		while (arrpaths[++i])
		{
			if ((cdpath = cd_test_cdpath(arrpaths[i], params)))
				break ;
		}
		ft_strarrdel(arrpaths);
	}
	else
		cdpath = cd_test_cdpath("./", params);
	return (path);
}

static void	cd_add_pwd(char **path)
{
	char	*pwd;
	size_t	size;
	char	*fullpath;

	if (!(pwd = getcwd(NULL, 0)))
		exit_perror(ENOMEM, NULL);
	size = ft_strlen(pwd);
	if (pwd[size - 1] == '/')
		fullpath = ft_strjoin(pwd, *path);
	else
		ft_sprintf(&fullpath, "%s/%s", pwd, *path);
	if (!fullpath)
		exit_perror(ENOMEM, NULL);
	free(*path);
	*path = fullpath;
}

static int	is_dot_component(char *path, int i)
{
	if (path[i] == '.' && (!i || path[i - 1] == '/')
			&& (path[i + 1] == '/' || path[i + 1] == '\0'))
		return (1);
	return (0);
}

static int	cd_remove_dot_slash(char *path, int i)
{
	int	len;

	len = path[i + 1] == '/' ? 2 : 1;
	ft_strmove(path + i, path + i + len);
	return (i);
}

static int	is_dot_dot_component(char *path, int i)
{
	if (path[i] == '.' && path[i + 1] == '.' && (!i || path[i - 1] == '/')
			&& (path[i + 2] == '/' || path[i + 2] == '\0'))
		return (1);
	return (0);
}

static int	correct_prev_component(char *path, int i)
{
	int	j;

	if (i > 1 && path[i - 1] == '/')
	{
		j = i - 1;
		while (j >= 0 && path[j] == '/')
			j--;
		if (!j)
			return (-1);
		while (j >= 0 && path[j] != '/')
			j--;
		if (path[j] == '/')
			j++;
		if (is_dot_dot_component(&(path[j]), 0))
			return (-1);
		return (j);
	}
	return (-1);
}

static int	cd_dot_dot_process(char *path, int i)
{
	int	j;
	int	len;

	if ((j = correct_prev_component(path, i)) != -1)
	{
		len = path[i + 2] == '/' ? 3 : 2;
		ft_strmove(path + j, path + i + len);
		return (j);
	}
	return (i);
}

static void	cd_change_canonical(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (is_dot_component(path, i))
			i = cd_remove_dot_slash(path, i);
		else if (is_dot_dot_component(path, i))
			i = cd_dot_dot_process(path, i);
		else if (path[i] != '/')
			while (path[i] && path[i] != '/')
				i++;
		else
			i++;
	}
}

int	utility_cd(char **av)
{
	char		*curpath;
	t_cd_params	params;

	curpath = NULL;
	cd_init_params(&params);
	cd_get_params(&params, &(av[1]));
	if (!params.dir && !ft_lstselect(g_env, "HOME", env_select_key))
		return (return_print("42sh: cd: HOME not set\n", -1));
	if (!params.dir && !(params.dir = get_env_value("HOME")))
		return (0);
	if (params.dir[0] != '/')
	{
		if (params.dir[0] != '.')
			curpath = cd_select_cdpath(&params);
		else if (!(curpath = ft_strdup(params.dir)))
			exit_perror(ENOMEM, NULL);
	}
	else if (!(curpath = ft_strdup(params.dir)))
		exit_perror(ENOMEM, NULL);
	// step 7
	if (!(params.P))
	{
		if (curpath[0] != '/')
			cd_add_pwd(&curpath);
		cd_change_canonical(curpath);
	}
	// step 10
	ft_printf("cd: %s\n", curpath);
	return (0);
}
