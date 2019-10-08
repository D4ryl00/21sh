/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 07:13:07 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/08 15:34:28 by rbarbero         ###   ########.fr       */
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

/*
** for stat
*/

#include <sys/types.h>
#include <sys/stat.h>

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

static char	*cd_select_cdpath(t_cd_params *params)
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

static int	cd_add_pwd(char **path)
{
	char	*pwd;
	size_t	size;
	char	*fullpath;

	if (!(pwd = getcwd(NULL, 0)))
		return (return_perror(ENOMEM, NULL, -1));
	size = ft_strlen(pwd);
	if (pwd[size - 1] == '/')
		fullpath = ft_strjoin(pwd, *path);
	else
		ft_sprintf(&fullpath, "%s/%s", pwd, *path);
	if (!fullpath)
	{
		free(pwd);
		return (return_perror(ENOMEM, NULL, -1));
	}
	free(pwd);
	free(*path);
	*path = fullpath;
	return (0);
}

static int	cd_remove_slash(char *path, int i)
{
	int	len;
	int	j;

	len = 0;
	j = i;
	while (path[++j] == '/')
		len++;
	if (len)
		ft_strmove(path + i + 1, path + i + len + 1);
	return (i + 1);
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

	if (i > 1)
	{
		j = i - 2;
		while (j >= 0 && path[j] != '/')
			j--;
		if (path[j] == '/')
			j++;
		return (j);
	}
	return (-1);
}

static int	cd_dot_dot_process(char *path, int i)
{
	int			prev;
	int			len;
	char		*tmp;
	struct stat	statbuf;

	len = path[i + 2] == '/' ? 3 : 2;
	if ((prev = correct_prev_component(path, i)) != -1)
	{
		if (!(tmp = ft_strndup(path, i - 1)))
			return (return_perror(ENOMEM, NULL, -1));
		if (stat(tmp, &statbuf) == -1)
			ft_perror(ENOENT, tmp, 0);
		else if ((statbuf.st_mode & S_IFMT) != S_IFDIR)
			ft_perror(ENOTDIR, tmp, 0);
		else
		{
			ft_strmove(path + prev, path + i + len);
			free(tmp);
			return (prev);
		}
		free(tmp);
		return (-1);
	}
	ft_strmove(path + i, path + i + len);
	return (i);
}

static int	cd_change_canonical(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			i = cd_remove_slash(path, i);
		else if (is_dot_component(path, i))
			i = cd_remove_dot_slash(path, i);
		else if (is_dot_dot_component(path, i))
		{
			if ((i = cd_dot_dot_process(path, i)) == -1)
			{
				free(path);
				return (-1);
			}
		}
		else
			i++;
	}
	return (0);
}

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

static t_list	*new_env_node(t_list **env)
{
	t_list	*entry;

	if (!(entry = (t_list *)malloc(sizeof(t_list))))
	{
		ft_perror(ENOMEM, NULL, 0);
		return (NULL);
	}
	entry->content = NULL;
	entry->content_size = 0;
	entry->next = NULL;
	ft_lstaddback(env, entry);
	return (entry);
}

void	set_oldpwd(t_list **env)
{
	t_list	*entry;
	char	*pwd;
	char	*value;

	if (!(pwd = env_get_value("PWD")))
		pwd = "";
	if (!(entry = ft_lstselect(*env, "OLDPWD", env_select_key)))
	{
		if (!(entry = new_env_node(env)))
			return ;
	}
	else
		free(entry->content);
	if (ft_sprintf(&value, "%s=%s", "OLDPWD", pwd) == -1)
	{
		free(pwd);
		ft_perror(ENOMEM, NULL, 0);
		return ;
	}
	entry->content = (void *)value;
	entry->content_size = ft_strlen(value) + 1;
}

void	set_pwd(t_list **env, const char *path)
{
	t_list	*entry;
	char	*value;

	if (!(entry = ft_lstselect(*env, "PWD", env_select_key)))
	{
		if (!(entry = new_env_node(env)))
			return ;
	}
	else
		free(entry->content);
	if (ft_sprintf(&value, "%s=%s", "PWD", path) == -1)
	{
		ft_perror(ENOMEM, NULL, 0);
		return ;
	}
	entry->content = (void *)value;
	entry->content_size = ft_strlen(value) + 1;
}

static int	cd_hyphen(void)
{
	char	*oldpwd;
	char	*av[3];
	int		status;

	status = 0;
	if (!(oldpwd = env_get_value("OLDPWD")) || !oldpwd[0])
		return (return_perror(EOTHER, "cd: OLDPWD not set", 1));
	if (!(oldpwd = ft_strdup(oldpwd)))
		return (return_perror(ENOMEM, NULL, 1));
	av[0] = "cd";
	av[1] = oldpwd;
	av[2] = NULL;
	if (!(status = utility_cd(av)))
		ft_printf("%s\n", oldpwd);
	free(oldpwd);
	return (status);
}

int	utility_cd(char **av)
{
	char		*curpath;
	t_cd_params	params;
	char		*pwd;

	curpath = NULL;
	cd_init_params(&params);
	cd_get_params(&params, &(av[1]));
	if (params.dir && params.dir[0] == '-' && !params.dir[1])
		return (cd_hyphen());
	// step 1, 2
	if (!params.dir && (!(params.dir = env_get_value("HOME"))
				|| !params.dir[0]))
		return (return_print("42sh: cd: HOME not set\n", 1));
	// step 3 and 4
	if (params.dir[0] != '/' && params.dir[0] != '.')
	{
		// step 5
		if (!(curpath = cd_select_cdpath(&params)))
			return (1);
	}
	// step 6
	else if (!(curpath = ft_strdup(params.dir)))
		return (return_perror(ENOMEM, NULL, 1));
	// step 7
	if (!(params.P))
	{
		if (curpath[0] != '/' && cd_add_pwd(&curpath) == -1)
		{
			free(curpath);
			return (1);
		}
		if (cd_change_canonical(curpath) == -1)
			return (1);
		if (!(pwd = ft_strdup(curpath)))
		{
			free(curpath);
			return (return_perror(ENOMEM, NULL, 1));
		}
		if (ft_strlen(curpath) + 1 >= PATH_MAX
				&& cd_reduce_curpath(curpath, &params) == -1)
		{
			ft_dprintf(2, "cd: file name too long: %s\n", curpath);
			free(curpath);
			return (1);
		}
	}
	// step 10
	if (chdir(curpath) == -1)
	{
		if (curpath)
			free(curpath);
		free(pwd);
		return (1);
	}
	if (params.P && !(pwd = getcwd(NULL, 0)))
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
