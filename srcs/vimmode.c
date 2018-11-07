/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vimmode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:59:04 by amordret          #+#    #+#             */
/*   Updated: 2018/11/07 18:57:33 by amordret         ###   ########.fr       */
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
	term_putstr_fd(VIMMODEPROMPT2, 2);
	while ((++i + 19) < (g_termcaps.promptlength))
		term_putchar(' ');
	term_putstr_fd(VIMMODEPROMPT3, 2);
	g_termcaps.writtenchars = 0;
}

static void	vim_special_char(t_read_input *s)
{
	s->c[3] = read(0, &(s->c[1]), 2);
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 68)
		return (input_is_left(&(s->cursorpos), s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 67)
		return (input_is_right(&(s->cursorpos), s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 51)
		return (input_is_del(&(s->cursorpos), &(s->buffer)));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 70)
		return (input_is_end(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 72)
		return (input_is_home(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 49)
		return (input_is_nextorprevword(s));
}

static void	highlight(t_read_input *s, int initialcursorpos, int cursorposbackup)
{
	if (((s->cursorpos >= cursorposbackup && s->cursorpos <= initialcursorpos)
	|| (s->cursorpos <= cursorposbackup && s->cursorpos >= initialcursorpos))
	&& ((initialcursorpos > 0)))
		ft_putstr_fd(g_termcaps.entervideomode, g_termcaps.fd);
	else
		ft_putstr_fd(g_termcaps.leavevideomode, g_termcaps.fd);
}

static void	reprint_all(t_read_input *s, int initialcursorpos)
{
	int	cursorposbackup;

	cursorposbackup = s->cursorpos;
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
	ft_putstr_fd(g_termcaps.deleteline, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.returnhome, g_termcaps.fd);
	vim_print_prompt(initialcursorpos);
	s->cursorpos = 0;
	while (s->buffer.buf[(s->cursorpos)])
	{
		highlight(s, initialcursorpos, cursorposbackup);
		ft_putchar_fd(s->buffer.buf[(s->cursorpos)], g_termcaps.fd);
		s->cursorpos++;
		g_termcaps.writtenchars++;
		if (get_cursorpos(s->cursorpos) == 0 /*&& get_cursorpos(cursorposbackup)*/)
			ft_putstr_fd(g_termcaps.cursordown, g_termcaps.fd);
	}
	while (s->cursorpos > cursorposbackup)
		input_is_left(&(s->cursorpos), s);
}

void		go_vim_mode(t_read_input *s)
{
	int	initialcursorpos;

	initialcursorpos = s->cursorpos;
	s->c[0] = 0;
	s->c[1] = 0;
	s->c[2] = 0;
	s->c[3] = 1;
	while (s->c[3] && s->c[0] != 22)
	{
		s->c[3] = read(0, &(s->c), 1);
		if (s->c[0] == 22)
			break ;
		if (s->c[0] == 127 || s->c[0] == 27 || s->c[0] == 3)
			vim_special_char(s);
		reprint_all(s, initialcursorpos);
	}
	reprint_all(s, -1);
}
