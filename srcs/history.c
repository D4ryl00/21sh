/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:49:18 by amordret          #+#    #+#             */
/*   Updated: 2018/05/15 17:36:11 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	open_history_file(void)
{
	if ((g_fd_history = open("~/.21sh",
	O_RDWR | O_CREAT | O_APPEND | S_IRWXG | S_IRWXO | S_IRWXU)) < 1)
	{
		termcaps_echo(1);
		ft_putstr(ERR_READ);
		termcaps_echo(0);
	}
}

void	close_history_file(void)
{
	if (g_fd_history > 1)
		close(g_fd_history);
}
