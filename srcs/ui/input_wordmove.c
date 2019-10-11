/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_wordmove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:01:12 by amordret          #+#    #+#             */
/*   Updated: 2019/10/11 12:05:09 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
