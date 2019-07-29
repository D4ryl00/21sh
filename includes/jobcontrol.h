/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/29 10:38:48 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

#include <unistd.h>

/*
** GLOBALS
*/

extern t_list	*g_asyncjobs;

/*
** STRUCTURES
*/

struct			s_job
{
	pid_t		pid;
	pid_t		pgid;
	int			forked;
	int			async;
	int			status;
};

/*
** PROTOTYPES
*/

void			init_job_struct(struct s_job *job);
pid_t			newjob(int *status, const unsigned char async);
void			waitjobs(void);

#endif
