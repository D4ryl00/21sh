/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:31:31 by amordret          #+#    #+#             */
/*   Updated: 2018/10/05 15:32:00 by amordret         ###   ########.fr       */
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
	s->tmpline = NULL;
	s->promptstring = promptstring;
	return (0);
}

/*static void	write_input(t_read_input *s)
{
	
	if ((s->c[3] > 1 && s->c[0] != '\n' && s->c[1] != 27 && s->c[1] != 0 &&
	ft_isprint(s->c[1]) == 1) || s->c[1] == '\n')
	{
		term_putchar(s->c[1]);
		if (s->c[1] != '\n')
			s->cursorpos += (ft_buf_insert_char(&(s->buffer), s->c[1], s->cursorpos) + 1);
	}
	if ((s->c[3] > 2 && s->c[1] != '\n' && s->c[2] != 27 && s->c[2] != 0 &&
	ft_isprint(s->c[2]) == 1) || s->c[2] == '\n')
	{
		term_putchar(s->c[2]);
		if (s->c[2] != '\n')
			s->cursorpos += (ft_buf_insert_char(&(s->buffer), s->c[2], s->cursorpos) + 1);
	}
}*/

int			read_input(t_input *input, char *promptstring)
{
	t_read_input	s;
	//char			c = 0;

	if ((set_t_read_input(&s, promptstring) == -1) || (ft_buf_init(&(s.buffer)) == -1))
		return (-1);
	while (s.c[3] && s.c[0] != '\n')
	{
		s.c[3] = read(0, &(s.c), 1);
		if (s.c[0] != 27 && (ft_isprint(s.c[0]) == 1) && (s.cursorpos +=
		ft_buf_insert_char(&(s.buffer), s.c[0], s.cursorpos) + 1) == -1)
			return (-1);
		if ((s.c[0] != 27 && s.c[0] != 0 && ft_isprint(s.c[0]) == 1) ||
		s.c[0] == '\n')
			term_putchar(s.c[0]);
		else if (s.c[0] == 127 || s.c[0] == 27 || s.c[0] == 3)
			input_is_special_char(&s);
		if (s.c[0] == 'c')
			ft_putnbr(get_cursorpos(s.cursorpos));
	}
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
