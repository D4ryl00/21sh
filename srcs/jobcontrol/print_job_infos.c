/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_job_infos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 07:31:56 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/16 10:58:47 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobcontrol.h"
#include "libft.h"

void	print_job_infos(struct s_job *job, const char *action)
{
	if (action)
		ft_dprintf(2, "[%u]\t%s\t%s\n", job->id, action, job->cmd);
	else
		ft_dprintf(2, "[%u]\t%s\n", job->id, job->cmd);
}
