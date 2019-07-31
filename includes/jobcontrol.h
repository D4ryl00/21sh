/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2019/07/31 12:41:31 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

# include <unistd.h>

# include "libft.h"

/*
** STRUCTURES
*/

struct					s_job
{
	unsigned int		job_id;
	pid_t				pid;
	pid_t				pgid;
	int					forked;
	int					async;
	int					status;
};

struct					s_jobctrl
{
	t_list				*asyncjobs;
	unsigned int		starting_job_id;
};

/*
** GLOBALS
*/

extern struct s_jobctrl	g_jobctrl;

/*
** PROTOTYPES
*/

void					init_job_struct(struct s_job *job);
int						newjob(struct s_job *job, int force_async);
int						waitjob(struct s_job *job);
void					waitjobs(int signal);

#endif
