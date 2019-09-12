/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 10:27:12 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/05 16:20:58 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** getpid
*/

#include <sys/types.h>
#include <unistd.h>

#include "sh.h"
#include "libft.h"
#include "jobcontrol.h"

/*
** Definition of global variables
*/

struct s_shell		g_shell = { -1, -1 };

struct s_jobctrl	g_jobctrl = { .jobs = NULL, .start_id = 1 };

/*
** Initialization of a struct s_shell.
*/

void	init_s_shell(void)
{
	g_shell.pid = getpid();
	g_shell.pgid = g_shell.pid;
	if (setpgid(g_shell.pid, g_shell.pgid) == -1)
		return_perror(EOTHER, "setpgid error");
}
