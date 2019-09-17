/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:59:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/17 18:36:28 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sigaction
*/

#include <signal.h>

#include "jobcontrol.h"
#include "signals.h"
#include "sh.h"

int	signals_init(void)
{
	struct sigaction	action;
	int					status;

	status = 0;
	ft_memset(&action, 0, sizeof(action));
	//action.sa_handler = &stop_job;
	action.sa_handler = SIG_IGN;
	status |= sigaction(SIGTSTP, &action, NULL);
	status |= sigaction(SIGINT, &action, NULL);
	status |= sigaction(SIGQUIT, &action, NULL);
	status |= sigaction(SIGTTIN, &action, NULL);
	status |= sigaction(SIGTTOU, &action, NULL);
	//status |= sigaction(SIGCHLD, &action, NULL);
	if (status)
		return_perror(EOTHER, "sigaction error");
	return (status);
}

int	signals_restore(void)
{
	struct sigaction	action;
	int					status;

	status = 0;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = SIG_DFL;
	status |= sigaction(SIGTSTP, &action, NULL);
	status |= sigaction(SIGINT, &action, NULL);
	status |= sigaction(SIGQUIT, &action, NULL);
	status |= sigaction(SIGTTIN, &action, NULL);
	status |= sigaction(SIGTTOU, &action, NULL);
	status |= sigaction(SIGCHLD, &action, NULL);
	return (status);
}
