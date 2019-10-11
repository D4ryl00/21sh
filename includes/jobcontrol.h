/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/10 16:30:02 by rbarbero         ###   ########.fr       */
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
	int					forked;
	int					child;
	int					nowait;
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
void					update_all_status_process(void);
int						update_status_process(pid_t pid, int status);
int						job_is_completed(struct s_job *job);
int						job_is_stopped(struct s_job *job);
struct s_process		*process_find(int pid, struct s_job **jobp);

#endif
