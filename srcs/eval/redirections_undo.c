/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_undo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:38:43 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 11:06:21 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include <sys/stat.h>

/*
** Init t_redirs with default values
*/

void	t_redirs_init(t_redirs *redirs)
{
	redirs->open = -1;
	redirs->dup_src = -1;
	redirs->dup_cpy = -1;
}

/*
** Free a t_redirs node in a t_list
*/

void	t_redirs_del(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

/*
** Save an fd if it exists
*/

int		t_redirs_save_fd(t_redirs *save, int fd)
{
	struct stat	buf;

	save->dup_src = fd;
	if (fstat(fd, &buf) != -1)
	{
		if ((save->dup_cpy = dup(fd)) == -1)
			return_perror(EDUP, NULL);
	}
	return (0);
}

/*
** Undo active redirections
*/

int		undo_redirs(t_list **redirs)
{
	while (*redirs)
	{
		if (((t_redirs *)(*redirs)->content)->dup_src != -1)
		{
			close(((t_redirs *)(*redirs)->content)->dup_src);
			if (((t_redirs *)(*redirs)->content)->dup_cpy != -1)
			{
				if (dup2(((t_redirs *)(*redirs)->content)->dup_cpy
						, ((t_redirs *)(*redirs)->content)->dup_src) == -1)
					exit_perror(EDUP, NULL);
				close(((t_redirs *)(*redirs)->content)->dup_cpy);
			}
		}
		ft_lstdelnode(redirs, *redirs, t_redirs_del);
	}
	return (0);
}
