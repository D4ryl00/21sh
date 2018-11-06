/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:14:03 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/05 15:10:22 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

#include <unistd.h>

/*
** GLOBALS
*/

extern t_list	*g_syncjobs;
extern t_list	*g_asyncjobs;

/*
** PROTOTYPES
*/

pid_t			newjob(int *status, const unsigned char async);
void			waitjobs(void);

#endif
