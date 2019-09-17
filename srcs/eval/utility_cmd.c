/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:29:58 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/17 19:05:53 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** exit
*/

#include <stdlib.h>

#include "libft.h"
#include "sh.h"
#include "eval.h"
#include "utilities.h"

char	*g_utility_cmd[] =
{
	"alias",
	"cd",
	"fg",
	""
};

int		is_utility_cmd(char **av)
{
	if (ft_strarrchr(av[0], g_utility_cmd) >= 0)
		return (1);
	return (0);
}

int		run_utility_cmd(char **av)
{
	int	status;

	status = 0;
	if (!g_jobctrl.current_job->forked
			|| (g_jobctrl.current_job->forked && g_jobctrl.current_job->child))
	{
		if (!ft_strcmp(av[0], "cd"))
			return(utility_cd(av));
		else if (!ft_strcmp(av[0], "fg"))
			return(utility_fg(av));
	}
	else if (!g_jobctrl.current_job->nowait && !g_jobctrl.current_job->async)
		status = waitjob(g_jobctrl.current_job);
	return (status);
}
