/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_select_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:12:14 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/09 16:17:20 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "utilities.h"

static char	*constuct_fullpath(char *path, t_cd_params *params)
{
	char	*fullpath;
	size_t	size;

	size = ft_strlen(path);
	if (path[size - 1] != '/')
		ft_sprintf(&fullpath, "%s/%s", path, params->dir);
	else
		fullpath = ft_strjoin(path, params->dir);
	if (!*fullpath)
	{
		ft_perror(ENOMEM, NULL, 0);
		return (NULL);
	}
	return (fullpath);
}

static int	cd_test_cdpath(char **fullpath, char *path, t_cd_params *params)
{
	int		status;

	status = 0;
	if (!(*fullpath = constuct_fullpath(path, params)))
		return (-1);
	if (access(*fullpath, F_OK) != -1)
	{
		if (access(*fullpath, X_OK) != -1)
			status = 1;
		else
		{
			status = -1;
			ft_perror(EACCES, params->dir, 0);
		}
	}
	if (status != 1)
	{
		free(*fullpath);
		*fullpath = NULL;
	}
	return (status);
}

char		*cd_select_cdpath(t_cd_params *params)
{
	char	*cdpath;
	char	**arrpaths;
	char	*path;
	int		i;
	int		status;

	path = NULL;
	if ((cdpath = env_get_value("CDPATH")) && cdpath[0])
	{
		if (!(arrpaths = ft_strsplit(cdpath, ':')))
		{
			ft_perror(ENOMEM, NULL, 0);
			return (NULL);
		}
		i = -1;
		while (arrpaths[++i])
			if ((status = cd_test_cdpath(&path, arrpaths[i], params)))
				break ;
		ft_strarrdel(arrpaths);
	}
	else
		status = cd_test_cdpath(&path, "./", params);
	if (!status)
		ft_perror(ENOENT, params->dir, 0);
	return (path);
}
