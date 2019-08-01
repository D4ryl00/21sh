/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:59:24 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/01 13:39:57 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sigaction
*/

#include <signal.h>

#include "jobcontrol.h"

int	signal_init(void)
{
	struct sigaction	action;
	struct sigaction	old;
	int					status;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &job_to_bg;
	status = sigaction(SIGTSTP, &action, &old);
	action.sa_handler = SIG_IGN;;
	status = sigaction(SIGTTIN, &action, &old);
	status = sigaction(SIGTTOU, &action, &old);
	return (status);
}
