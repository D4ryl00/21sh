/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misctools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:15:42 by amordret          #+#    #+#             */
/*   Updated: 2019/10/11 13:11:17 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_cursorpos(int cursorpos)
{
	struct winsize	ws;

	if ((ioctl(g_termcaps.fd, TIOCGWINSZ, &ws)) == -1)
		return (-1);
	if (!ws.ws_col)
		ws.ws_col = 40;
	return ((cursorpos + g_termcaps.promptlength) % ws.ws_col);
}

int		termcaps_clearline(t_read_input *s)
{
	input_is_end(s);
	while (s->cursorpos)
	{
		ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
		input_is_left(&(s->cursorpos), s);
		if (get_cursorpos(s->cursorpos) == 0)
			ft_putstr_fd(g_termcaps.deleteline, g_termcaps.fd);
		if (g_termcaps.writtenchars > 0)
			g_termcaps.writtenchars = g_termcaps.writtenchars - 1;
	}
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	return (0);
}
