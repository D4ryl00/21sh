/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:31:31 by amordret          #+#    #+#             */
/*   Updated: 2018/10/30 16:51:32 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	set_t_read_input(t_read_input *s, char *promptstring)
{
	s->c[0] = 0;
	s->c[1] = 0;
	s->c[2] = 0;
	s->c[3] = 1;
	s->cursorpos = 0;
	s->historynb = 0;
	s->cursorposinline = 0;
	s->cursorline = 0;
	s->tmpline = NULL;
	s->promptstring = promptstring;
	return (0);
}

void		reprint_after(t_read_input *s)
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
	while (s->buffer.buf[(s->cursorpos)])
	{
		ft_putchar_fd(s->buffer.buf[(s->cursorpos)], g_termcaps.fd);
		s->cursorpos++;
		if (get_cursorpos(s->cursorpos) == 0 /*&& get_cursorpos(cursorposbackup)*/)
			ft_putstr_fd(g_termcaps.cursordown, g_termcaps.fd);
	}
	while (s->cursorpos > cursorposbackup)
		input_is_left(&(s->cursorpos), s);
}

void		cursorposplusone(t_read_input *s)
{
	s->cursorpos = s->cursorpos + 1;
	if (get_cursorpos(s->cursorpos) == 0)
	{
		s->cursorline++;
		s->cursorposinline = 0;
	}
	else
		s->cursorposinline = s->cursorposinline + 1;
}


void		cursorposminusone(t_read_input *s)
{
	if (get_cursorpos(s->cursorpos) == 0)
	{
		s->cursorline < 1 ? s->cursorline : s->cursorline--;
		s->cursorposinline = get_real_windows_width();
	}
	s->cursorpos < 1 ? s->cursorpos : s->cursorpos--;
}

static int	read_input_loop(t_read_input *s)
{
	s->c[3] = read(0, &(s->c), 1);
	if (s->c[0] != 27 && (ft_isprint(s->c[0]) == 1) && (
	ft_buf_insert_char(&(s->buffer), s->c[0], s->cursorpos)) == -1 && ((s->cursorposinline++) == -1))
		return (-1);
	cursorposplusone(s);
	/*
	//DEBUG SORTIE ERREUR
	ft_putstr_fd("cursorpos ", 2);
	ft_putnbr_fd(s->cursorpos, 2);
	ft_putstr_fd(" cursorline ", 2);
	ft_putnbr_fd(s->cursorline, 2);
	ft_putstr_fd("cursorposinline ", 2);
	ft_putnbr_fd(s->cursorposinline, 2);
	ft_putchar_fd('\n', 2);
	// FIN DEBUG SORTIE ERREUR
	*/
	if ((s->c[0] != 27 && s->c[0] != 0 && ft_isprint(s->c[0]) == 1) ||
	s->c[0] == '\n')
	{
		term_putchar(s->c[0]);
		if (get_cursorpos(s->cursorpos) == 0)
			ft_putstr_fd(g_termcaps.cursordown, g_termcaps.fd);
	}
	else if (s->c[0] == 127 || s->c[0] == 27 || s->c[0] == 3)
		input_is_special_char(s);
	reprint_after(s);
	return (0);
}

int			read_input(t_input *input, char *promptstring)
{
	t_read_input	s;

	if ((set_t_read_input(&s, promptstring) == -1) || (ft_buf_init(&(s.buffer)) == -1))
		return (-1);
	while (s.c[3] && s.c[0] != '\n')
		if (read_input_loop(&s) == -1)
			return (-1);
	if (ft_buf_add_char(&(s.buffer), '\n') == -1 ||
	ft_buf_add_char(&(s.buffer), '\0') == -1 || !((input->str) = ft_buf_flush(&(s.buffer))))
		return (-1);
	if (s.promptstring && input->str && (ft_strlen(input->str)) > 1)
		append_line_to_prev_hist(input->str);
	else if (input->str && (ft_strlen(input->str)) > 1)
		add_to_command_hist(input->str);
	input->save = &(input->str[0]);
	ft_buf_destroy(&(s.buffer));
	if (s.tmpline)
		free(s.tmpline);
	return (s.c[3]);
}