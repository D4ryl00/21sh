/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_homeend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:23:11 by amordret          #+#    #+#             */
/*   Updated: 2018/09/24 14:33:29 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_end(t_read_input *s)
{
	while (s->cursorpos < g_termcaps.writtenchars)
	{
		ft_putstr_fd(g_termcaps.cursorright, 0);
		s->cursorpos++;
	}
}

void	input_is_home(t_read_input *s)
{
	while (s->cursorpos > 0)
	{
		ft_putstr_fd(g_termcaps.cursorleft, 0);
		s->cursorpos--;
	}
}

void	input_is_prevword(t_read_input *s)
{
	int	i;

	i = s->cursorpos;
	while (i > 0 && s->buffer.buf && s->buffer.buf[i] != ' ')
	{
		ft_putstr_fd(g_termcaps.cursorleft, 0);
		(s->cursorpos)--;
		i--;
	}
	if (i > 0)
	{
		ft_putstr_fd(g_termcaps.cursorleft, 0);
		(s->cursorpos)--;
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
		ft_putstr_fd(g_termcaps.cursorright, 0);
		(s->cursorpos)++;
		i++;
	}
	if (s->buffer.buf && s->buffer.buf[i++])
	{
		ft_putstr_fd(g_termcaps.cursorright, 0);
		(s->cursorpos)++;
	}
}

void	input_is_nextorprevword(t_read_input *s)
{
	char	c;

	c = 0;
	if (s->c[1] == 98)
		return (input_is_prevword(s));
	if (s->c[1] == 102)
		return (input_is_nextword(s));
	read(0, &c, 1);
	if (c == 'D' || c == 'd')
		return (input_is_prevword(s));
	if (c == 'C' || c == 'c')
		return (input_is_nextword(s));
}