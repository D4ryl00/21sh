/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:59:04 by amordret          #+#    #+#             */
/*   Updated: 2018/11/09 11:17:53 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	vim_special_char(t_read_input *s)
{
	if (s->c[0] == 27 && esc_was_pressed(s))
	{
		s->c[0] = 'v';
		return ;
	}
	if ((s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 68) || s->c[0] == 'h')
		return (input_is_left(&(s->cursorpos), s));
	if ((s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 67) || s->c[0] == 'l')
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

static void	init_visualmode(t_read_input *s, int *initialcursorpos)
{
	*initialcursorpos = s->cursorpos;
	s->c[0] = 0;
	s->c[1] = 0;
	s->c[2] = 0;
	s->c[3] = 1;
	visualmode_reprint_all(s, s->cursorpos, s->cursorpos);
}

static void	visualmode_d(t_read_input *s, char **yanked, int initialcursorpos)
{
	if (d_was_pressed_again(s))
	{
		input_is_end(s);
		s->cursorpos = s->buffer.i;
		return (vimcut(0, s, yanked));
	}
	return (vimcut(initialcursorpos, s, yanked));
}

void		visualmode(t_read_input *s, char **yanked)
{
	int		initialcursorpos;

	init_visualmode(s, &initialcursorpos);
	while (s->c[3] && s->c[0] != 22)
	{
		s->c[3] = read(0, &(s->c), 1);
		if (s->c[0] == 127 || s->c[0] == 27 || s->c[0] == 3 || s->c[0] == 'h' ||
		s->c[0] == 'j' || s->c[0] == 'k' || s->c[0] == 'l')
			vim_special_char(s);
		if (s->c[0] == 22 || s->c[0] == 'v')
		{
			s->c[0] = 0;
			return ;
		}
		if (s->c[0] == 'y')
			return (yank(initialcursorpos, s, yanked));
		if (s->c[0] == 'd')
			return (visualmode_d(s, yanked, initialcursorpos));
		visualmode_reprint_all(s, initialcursorpos, s->cursorpos);
	}
}
