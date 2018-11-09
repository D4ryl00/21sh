/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vimmisctools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:08:08 by amordret          #+#    #+#             */
/*   Updated: 2018/11/09 11:16:56 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	vimcut(int initialcursorpos, t_read_input *s, char **yanked)
{
	int a;
	int b;
	int i;

	i = 0;
	yank(initialcursorpos, s, yanked);
	startend(initialcursorpos, s->cursorpos, &a, &b);
	while (b >= (a + i) && ((a) < s->buffer.i))
	{
		ft_buf_delete_char(&(s->buffer), a);
		i++;
	}
}

void	highlight(t_read_input *s, int initialcursorpos, int cursorposbackup)
{
	if (((s->cursorpos >= cursorposbackup && s->cursorpos <= initialcursorpos)
	|| (s->cursorpos <= cursorposbackup && s->cursorpos >= initialcursorpos))
	&& ((initialcursorpos >= 0)))
		ft_putstr_fd(g_termcaps.entervideomode, g_termcaps.fd);
	else
		ft_putstr_fd(g_termcaps.leavevideomode, g_termcaps.fd);
}

int		d_was_pressed_again(t_read_input *s)
{
	int				yes;
	struct timespec ts;

	ts.tv_nsec = 100000000L;
	ts.tv_sec = 0;
	yes = 1;
	g_termcaps.current_termios.c_cc[VMIN] = 0;
	g_termcaps.current_termios.c_cc[VTIME] = 1;
	tcsetattr(g_termcaps.fd, TCSANOW, &(g_termcaps.current_termios));
	nanosleep(&ts, NULL);
	if ((s->c[3] = read(0, &(s->c[0]), 1)) == 0)
	{
		yes = 0;
		s->c[3] = 1;
	}
	if (yes && s->c[0] != 'd')
		yes = 0;
	g_termcaps.current_termios.c_cc[VMIN] = 1;
	g_termcaps.current_termios.c_cc[VTIME] = 0;
	tcsetattr(g_termcaps.fd, TCSANOW, &(g_termcaps.current_termios));
	return (yes);
}
