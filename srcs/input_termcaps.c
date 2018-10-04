/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:51:27 by amordret          #+#    #+#             */
/*   Updated: 2018/10/04 10:25:04 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	input_is_left(int *cursorpos)
{
	if (*cursorpos == 0)
		return ;
	ft_putstr_fd(g_termcaps.cursorleft, 0);
	(*cursorpos)--;
}

static void	input_is_right(int *cursorpos)
{
	if (*cursorpos >= g_termcaps.writtenchars)
		return ;
	ft_putstr_fd(g_termcaps.cursorright, 0);
	(*cursorpos)++;
}

static void	input_is_del(int *cursorpos, t_buf *buffer)
{
	char c;

	read(0, &c, 1);
	if (*cursorpos == buffer->i)
		return ;
	ft_buf_delete_char(buffer, *(cursorpos));
	ft_putstr_fd(g_termcaps.delete, 0);
	if (g_termcaps.writtenchars)
		g_termcaps.writtenchars--;
}

void		input_is_backspace(int *cursorpos, t_buf *buffer)
{
	if (*cursorpos == 0)
		return ;
	input_is_left(cursorpos);
	ft_buf_delete_char(buffer, *(cursorpos));
	ft_putstr_fd(g_termcaps.delete, 0);
	if (g_termcaps.writtenchars)
		g_termcaps.writtenchars--;
}

void		input_is_special_char(t_read_input *s)
{
	if (s->c[0] == 127)
		return (input_is_backspace(&(s->cursorpos), &(s->buffer)));
	if (s->c[0] == 3)
		termcaps_reset_term_and_exit();
	s->c[3] = read(0, &(s->c[1]), 2);
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 68)
		return (input_is_left(&(s->cursorpos)));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 67)
		return (input_is_right(&(s->cursorpos)));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 51)
		return (input_is_del(&(s->cursorpos), &(s->buffer)));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 65 &&
	!(max_history_reached(s)))
		return (input_is_up(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 66 && s->historynb)
		return (input_is_down(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 70)
		return (input_is_end(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 72)
		return (input_is_home(s));
	if (s->c[0] == 27 && s->c[1] == 91 && s->c[2] == 49)
		return (input_is_nextorprevword(s));
}
