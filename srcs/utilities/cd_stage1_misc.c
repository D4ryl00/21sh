/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_stage1_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 13:23:40 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "utilities.h"

void	cd_init_params(t_cd_params *params)
{
	params->l = 0;
	params->p = 0;
	params->dir = NULL;
}

void	cd_get_params(t_cd_params *params, char **av)
{
	while (*av)
	{
		if ((*av)[0] == '-' && (*av)[1] == 'L')
		{
			params->l = 1;
			params->p = 0;
		}
		else if ((*av)[0] == '-' && (*av)[1] == 'P')
		{
			params->l = 1;
			params->p = 0;
		}
		else
		{
			params->dir = (*av)[0] ? *av : NULL;
			break ;
		}
		av++;
	}
}

int		cd_add_pwd(char **path)
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
