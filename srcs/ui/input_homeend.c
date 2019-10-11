/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_homeend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:23:11 by amordret          #+#    #+#             */
/*   Updated: 2019/10/07 18:17:41 by amordret         ###   ########.fr       */
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
	while (s->cursorpos > 0 /*&& get_cursorpos(s->cursorpos)*/)
	{
		//ft_putstr_fd(g_termcaps.cursorleft, 0);
		//s->cursorpos--;
		input_is_left(&(s->cursorpos), s);
	}
}

void	input_is_prevword(t_read_input *s)
{
	int	i;

	i = s->cursorpos;
	while (i > 0 && s->buffer.buf && s->buffer.buf[i] != ' ')
	{
		input_is_left(&(s->cursorpos), s);
		i--;
	}
	if (i > 0)
	{
		input_is_left(&(s->cursorpos), s);
	}
}

void	input_is_nextword(t_read_input *s)
{
	int	i;

	i = 0;
	while (s->buffer.buf && s->buffer.buf[i] && i < s->cursorpos)
		i++;
	while (s->buffer.buf && s->buffer.buf[i] && (s->buffer.buf[i] != ' '))
	{
		input_is_right(&(s->cursorpos), s);
		i++;
	}
	if (s->buffer.buf && s->buffer.buf[i++])
	{
		input_is_right(&(s->cursorpos), s);
	}
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

void	input_is_nextorprevword(t_read_input *s)
{
	char	c;

	c = 0;
	read(0, &c, 1);
	read(0, &c, 1);
	c = 0;
	read(0, &c, 1);
	if (c == 'D' || c == 'd')
		return (input_is_prevword(s));
	if (c == 'C' || c == 'c')
		return (input_is_nextword(s));
	if (c == 'A' || c == 'a')
		return (input_is_upline(s));
	if (c == 'B' || c == 'b')
		return (input_is_downline(s));
}