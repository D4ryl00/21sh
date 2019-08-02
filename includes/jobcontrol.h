/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2019/08/02 11:37:47 by rbarbero         ###   ########.fr       */
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
	int					child;
	int					forked;
	int					async;
	int					stopped;
	int					completed;
	int					status;
};

struct					s_jobctrl
{
	struct s_job		job;
	t_list				*asyncjobs;
	unsigned int		starting_job_id;
};

struct							s_shell
{
	pid_t						pid;
	pid_t						pgid;
};

/*
** GLOBALS
*/

extern struct s_jobctrl	g_jobctrl;
extern struct s_shell	g_shell;

/*
** PROTOTYPES
*/

void					init_s_shell(void);
void					init_job_struct(void);
int						newjob(int force_async);
int						waitjob(void);
void					waitjobs(int signal);
void					job_to_bg(int signal);
void					del_job_node(void *content, size_t content_size);
int						test_job_node(t_list *node, void *data);

#endif
