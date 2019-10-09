/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dot_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:06:46 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/09 16:19:36 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stat
*/

#include <sys/stat.h>

#include "sh.h"
#include "libft.h"

int			cd_is_dot_dot_component(char *path, int i)
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

int			cd_dot_dot_process(char *path, int i)
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
