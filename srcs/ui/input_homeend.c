/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_homeend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:23:11 by amordret          #+#    #+#             */
/*   Updated: 2019/10/11 12:01:35 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_end(t_read_input *s)
{
	input_is_home(s);
	while (s->cursorpos < g_termcaps.writtenchars)
		input_is_right(&s->cursorpos, s);
}

void	input_is_home(t_read_input *s)
{
	while (s->cursorpos > 0)
		input_is_left(&(s->cursorpos), s);
}

void	input_is_upline(t_read_input *s)
{
	int				i;
	struct winsize	ws;

	if ((ioctl(g_termcaps.fd, TIOCGWINSZ, &ws)) == -1)
		return ;
	if (!(s->cursorpos / ws.ws_col))
		return (input_is_home(s));
	i = ws.ws_col;
	while (i)
	{
		input_is_left(&s->cursorpos, s);
		i--;
	}
}

void	input_is_downline(t_read_input *s)
{
	int				i;
	struct winsize	ws;

	if ((ioctl(g_termcaps.fd, TIOCGWINSZ, &ws)) == -1)
		return ;
	if ((s->cursorpos + ws.ws_col) > s->buffer.i)
		return (input_is_end(s));
	i = ws.ws_col;
	while (i)
	{
		input_is_right(&s->cursorpos, s);
		i--;
	}
}
