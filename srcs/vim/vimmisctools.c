/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vimmisctools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:41:32 by amordret          #+#    #+#             */
/*   Updated: 2018/11/08 17:08:45 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	vim_paste(t_read_input *s, char **yanked)
{
	int	i;

	i = -1;
	while ((*yanked)[++i])
	{
		ft_buf_insert_char(&(s->buffer), (*yanked)[i], s->cursorpos + i);
	}
}

void	startend(int initialcursorpos, int cursorpos, int *a, int *b)
{
	if (initialcursorpos <= cursorpos)
	{
		*a = initialcursorpos;
		*b = cursorpos;
	}
	else
	{
		*a = cursorpos;
		*b = initialcursorpos;
	}
}

void	vim_free_yanked(char **yanked)
{
	if (*yanked)
		free(*yanked);
	free(yanked);
}

void	yank(int initialcursorpos, t_read_input *s, char **yanked)
{
	int a;
	int b;
	int i;

	i = -1;
	startend(initialcursorpos, s->cursorpos, &a, &b);
	if ((*yanked))
		free(*yanked);
	if ((*yanked = malloc(b - a + 2)) == NULL)
		exit_perror(ENOMEM, NULL);
	while (b >= a && ++i < 999999 && (s->buffer.buf)[a])
	{
		(*yanked)[i] = (s->buffer.buf)[a];
		a++;
	}
	(*yanked)[i + 1] = '\0';
}

int		esc_was_pressed(t_read_input *s)
{
	int	yes;

	yes = 0;
	g_termcaps.current_termios.c_cc[VMIN] = 0;
	g_termcaps.current_termios.c_cc[VTIME] = 1;
	tcsetattr(g_termcaps.fd, TCSANOW, &(g_termcaps.current_termios));
	if ((s->c[3] = read(0, &(s->c[1]), 2)) == 0)
	{
		yes = 1;
		s->c[3] = 1;
	}
	g_termcaps.current_termios.c_cc[VMIN] = 1;
	g_termcaps.current_termios.c_cc[VTIME] = 0;
	tcsetattr(g_termcaps.fd, TCSANOW, &(g_termcaps.current_termios));
	return (yes);
}
