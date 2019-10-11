/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rightleft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:03:24 by amordret          #+#    #+#             */
/*   Updated: 2019/10/01 17:03:48 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_left(int *cursorpos, t_read_input *s)
{
	int	i;

	i = 0;
	if (*cursorpos == 0 && (get_cursorpos(*cursorpos) >= 1))
		return ;
	if (s->buffer.buf && s->cursorpos <= s->buffer.i && s->cursorpos > 0 && (s->buffer.buf[s->cursorpos - 1] == '\n' || get_cursorpos(*cursorpos) == 0))
	{
		i = s->cursorpos - 1;
		ft_putstr_fd(g_termcaps.cursorup, g_termcaps.fd);
		while (--i >= 0 && s->buffer.buf[i] != '\n')
		{
			ft_putstr_fd(g_termcaps.cursorright, g_termcaps.fd);
			if (i == 0)
			{
				i = g_termcaps.promptlength + 1;
				while (--i > 0)
				ft_putstr_fd(g_termcaps.cursorright, g_termcaps.fd);
			}
		}
	}
	else
		ft_putstr_fd(g_termcaps.cursorleft, g_termcaps.fd);
	(*cursorpos)--;
}

void		input_is_right(int *cursorpos, t_read_input *s)
{
	if (*cursorpos >= g_termcaps.writtenchars)
		return ;
	(*cursorpos)++;
	if (get_cursorpos(*cursorpos) == 0 || (s->buffer.buf && s->cursorpos <= s->buffer.i && s->cursorpos > 0 && s->buffer.buf[s->cursorpos] && s->buffer.buf[s->cursorpos - 1] == '\n'))
		ft_putstr_fd(g_termcaps.cursordown, g_termcaps.fd);
	else
		ft_putstr_fd(g_termcaps.cursorright, 0);
}