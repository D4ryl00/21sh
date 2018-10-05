/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misctools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:15:42 by amordret          #+#    #+#             */
/*   Updated: 2018/10/05 15:58:01 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_cursorpos(int cursorpos)
{
	struct	winsize	ws;

	if ((ioctl(g_termcaps.fd, TIOCGWINSZ, &ws)) == -1)
		return (-1);
	return ((cursorpos + g_termcaps.promptlength) % ws.ws_col);
}

int		get_windows_width(void)
{
	struct	winsize	ws;

	return (ioctl(g_termcaps.fd, TIOCGWINSZ, &ws));
}

void	term_putchar(char c)
{
	termcaps_echo(1);
	ft_putchar(c);
	g_termcaps.writtenchars++;
	termcaps_echo(0);
}

void	term_putstr(char *s)
{
	termcaps_echo(1);
	ft_putstr(s);
	g_termcaps.writtenchars += ft_strlen(s);
	termcaps_echo(0);
}

/*int		termcaps_clearlineandbuff(t_read_input *s)
{
	ft_putstr_fd(g_termcaps.returnhome, 0);
	ft_putstr_fd(g_termcaps.deleteline, 0);
	if (s && s->cursorpos)
		s->cursorpos = 0;
	ft_buf_destroy(&(s->buffer));
	if (ft_buf_init(&(s->buffer)) == -1)
		return (-1);
	prompt(NULL);
	return (0);
}*/

int		termcaps_clearline(t_read_input *s)
{
	ft_putstr_fd(g_termcaps.returnhome, g_termcaps.fd);
	ft_putstr_fd(g_termcaps.deleteline, g_termcaps.fd);
	if (s && s->cursorpos)
		s->cursorpos = 0;
	prompt(s->promptstring);
	/*input_is_end(s);
	while (s->cursorpos)
		input_is_backspace(&(s->cursorpos), &(s->buffer));*/
	return (0);
}
