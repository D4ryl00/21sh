/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_list_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:45:00 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/01 10:46:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free
*/

#include <stdlib.h>

#include "libft.h"
#include "jobcontrol.h"

void	del_job_node(void *content, size_t content_size)
{
	(void)content_size;
	if (content)
		free(content);
}

int		test_job_node(t_list *node, void *data)
{
	if (((struct s_job *)node->content)->pgid == *(pid_t *)data)
		return (1);
	return (0);
}
