/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_homeend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:23:11 by amordret          #+#    #+#             */
/*   Updated: 2018/09/20 16:09:15 by amordret         ###   ########.fr       */
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
