/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vimmode2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:34:12 by amordret          #+#    #+#             */
/*   Updated: 2018/11/09 11:03:42 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	vimmode_reprint_all2(t_read_input *s, int initialcursorpos)
{
	ft_putstr_fd(g_termcaps.deleteline, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.returnhome, g_termcaps.fd);
	vimmode_print_prompt(initialcursorpos);
	s->cursorpos = 0;
}

void		vimmode_reprint_all(t_read_input *s, int initialcursorpos)
{
	int	cursorposbackup;

	cursorposbackup = s->cursorpos;
	if (s->cursorpos == 1)
		return ;
	while (s->cursorpos < g_termcaps.writtenchars)
		input_is_right(&(s->cursorpos), s);
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.deletetoend, g_termcaps.fd);
	while (s->cursorpos > 0)
	{
		input_is_left(&(s->cursorpos), s);
		ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	}
	vimmode_reprint_all2(s, initialcursorpos);
	while (s->buffer.buf[(s->cursorpos)])
	{
		ft_putchar_fd(s->buffer.buf[(s->cursorpos)], g_termcaps.fd);
		s->cursorpos++;
		g_termcaps.writtenchars++;
		if (get_cursorpos(s->cursorpos) == 0)
			ft_putstr_fd(g_termcaps.cursordown, g_termcaps.fd);
	}
	while (s->cursorpos > cursorposbackup)
		input_is_left(&(s->cursorpos), s);
}
