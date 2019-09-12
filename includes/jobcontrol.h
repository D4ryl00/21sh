/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2019/09/12 09:01:50 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

# include <unistd.h>

/*
** struct termios
*/

# include <termios.h>

# include "libft.h"

/*
** STRUCTURES
*/

struct					s_process
{
	pid_t				pid;
	int					completed;
	int					stopped;
	int					status;
};

struct					s_job
{
	unsigned int		id;
	char				*cmd;
	pid_t				pgid;
	int					child;
	int					async;
	int					notified;
	struct termios		tmodes;
	t_list				*processes;
};

struct					s_jobctrl
{
	t_list				*jobs;
	struct s_job		*current_job;
	unsigned int		start_id;
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
struct s_job			*newjob(int async);
int						newprocess(struct s_job *job);
int						waitjob(struct s_job *job);
void					do_job_notification(void);
void					stop_job(int signal);
void					del_job_node(void *content, size_t content_size);
int						test_job_node(t_list *node, void *data);
void					print_job_infos(struct s_job *job, const char *action);
int						get_job_status(struct s_job *job);

#endif
