/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_to_canonical.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:57 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/09 16:16:53 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"
#include "utilities.h"

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

static int	cd_is_dot_component(char *path, int i)
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

int			cd_path_to_canonical(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			i = cd_remove_slash(path, i);
		else if (cd_is_dot_component(path, i))
			i = cd_remove_dot_slash(path, i);
		else if (cd_is_dot_dot_component(path, i))
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
