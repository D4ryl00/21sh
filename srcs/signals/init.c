/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:59:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/02 10:21:05 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sigaction
*/

#include <signal.h>

#include "jobcontrol.h"
#include "sh.h"

int	signals_init(void)
{
	struct sigaction	action;
	struct sigaction	old;
	int					status;

	status = 0;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &job_to_bg;
	status |= sigaction(SIGTSTP, &action, &old);
	action.sa_handler = SIG_IGN;;
	status |= sigaction(SIGINT, &action, &old);
	status |= sigaction(SIGQUIT, &action, &old);
	status |= sigaction(SIGTTIN, &action, &old);
	status |= sigaction(SIGTTOU, &action, &old);
	status |= sigaction(SIGCHLD, &action, &old);
	if (status)
		return_perror(EOTHER, "sigaction error");
	return (status);
}

int	signals_restore(void)
{
	struct sigaction	action;
	struct sigaction	old;
	int					status;

	status = 0;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = SIG_DFL;
	status |= sigaction(SIGTSTP, &action, &old);
	status |= sigaction(SIGINT, &action, &old);
	status |= sigaction(SIGQUIT, &action, &old);
	status |= sigaction(SIGTTIN, &action, &old);
	status |= sigaction(SIGTTOU, &action, &old);
	status |= sigaction(SIGCHLD, &action, &old);
	return (status);
}
