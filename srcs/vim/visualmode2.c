/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualmode2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:48:25 by amordret          #+#    #+#             */
/*   Updated: 2018/11/08 17:05:24 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	vim_print_prompt(int initialcursorpos)
{
	int	i;

	i = -1;
	if (initialcursorpos < 0)
		return (prompt(NULL));
	term_putstr_fd(VIMMODEPROMPT1, 2);
	while ((++i + 9) < (g_termcaps.promptlength / 2))
		term_putchar(' ');
	term_putstr_fd(VIMINSERTMODEPROMPT2, 2);
	while ((++i + 16) < (g_termcaps.promptlength))
		term_putchar(' ');
	term_putstr_fd(VIMMODEPROMPT3, 2);
	g_termcaps.writtenchars = 0;
}

static void	visualmode_reprint_all2(t_read_input *s, int initialcursorpos)
{
	ft_putstr_fd(g_termcaps.deleteline, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.returnhome, g_termcaps.fd);
	vim_print_prompt(initialcursorpos);
	s->cursorpos = 0;
}

void		visualmode_reprint_all(t_read_input *s, int initialcursorpos,
int cursorposbackup)
{
	if (s->cursorpos == 1)
		return ;
	while (s->cursorpos < g_termcaps.writtenchars)
		input_is_right(&(s->cursorpos), s);
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.deletetoend, g_termcaps.fd);
	while (s->cursorpos > cursorposbackup)
	{
		input_is_left(&(s->cursorpos), s);
		ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	}
	visualmode_reprint_all2(s, initialcursorpos);
	while (s->buffer.buf[(s->cursorpos)])
	{
		highlight(s, initialcursorpos, cursorposbackup);
		ft_putchar_fd(s->buffer.buf[(s->cursorpos)], g_termcaps.fd);
		s->cursorpos++;
		g_termcaps.writtenchars++;
		if (get_cursorpos(s->cursorpos) == 0)
			ft_putstr_fd(g_termcaps.cursordown, g_termcaps.fd);
	}
	while (s->cursorpos > cursorposbackup)
		input_is_left(&(s->cursorpos), s);
}
