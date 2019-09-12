/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_job_infos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 07:31:56 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/12 20:38:19 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobcontrol.h"
#include "libft.h"

void	print_job_infos(struct s_job *job, const char *action)
{
	if (action)
		dprintf(2, "[%u]\t%s\t%s\n", job->id, action, job->cmd);
	else
		dprintf(2, "[%u]\t%s\n", job->id, job->cmd);
}
