/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:29:58 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/20 09:01:18 by rbarbero         ###   ########.fr       */
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
	"bg",
	"jobs",
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
			status = utility_cd(av);
		else if (!ft_strcmp(av[0], "fg"))
			status = utility_fg(av);
		else if (!ft_strcmp(av[0], "bg"))
			status = utility_bg(av);
		else if (!ft_strcmp(av[0], "jobs"))
			status = utility_jobs(av);
		if (g_jobctrl.current_job->child)
			exit(status);
	}
	else if (!g_jobctrl.current_job->nowait && !g_jobctrl.current_job->async)
		status = waitjob(g_jobctrl.current_job);
	return (status);
}
