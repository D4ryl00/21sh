/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/12/20 14:19:06 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

#include <unistd.h>
#include <termios.h>

/*
** GLOBALS
*/

extern t_list	*g_asyncjobs;

/*
** STRUCTURES
*/

typedef struct		s_process
{
	char			**argv;
	pid_t			pid;
	unsigned char	completed;
	unsigned char	stopped;
	int				status;
	int				stdin;
	int				stdout;
	int				stderr;
}					t_process;

typedef struct		s_job
{
	char			*command;
	t_list			*process;
	pid_t			pgid;
	unsigned char	notified;
	struct termios	tmodes;
}					t_job;

/*
** PROTOTYPES
*/

pid_t			newjob(int *status, const unsigned char async);
//void			waitjobs(void);
int				waitjob(t_job *job);

#endif
