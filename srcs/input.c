/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:31:31 by amordret          #+#    #+#             */
/*   Updated: 2018/09/17 15:50:56 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	set_t_read_input(t_read_input *s)
{
	s->c[0] = 0;
	s->c[3] = 1;
	s->cursorpos = 0;
	s->historynb = 0;
	s->tmpline = NULL;
}

int			read_input(t_input *input)
{
	t_read_input	s;

	set_t_read_input(&s);
	if (ft_buf_init(&(s.buffer)) == -1)
		return (-1);
	while (s.c[3] && s.c[0] != '\n')
	{
		s.c[3] = read(0, &(s.c), 3);
		if (s.c[0] != 27 && ft_isprint(s.c[0]) == 1 && (s.cursorpos +=
		ft_buf_insert_char(&(s.buffer), s.c[0], s.cursorpos) + 1) == -1)
			return (-1);
		if ((s.c[0] != 27 && s.c[0] != 0 && ft_isprint(s.c[0]) == 1) ||
		s.c[0] == '\n')
			term_putchar(s.c[0]);
		else
			input_is_special_char(&s);
		if (s.c[0] == '?')
			termcaps_reset_term_and_exit();
	}
	if (ft_buf_add_char(&(s.buffer), '\0') == -1 ||
	!((input->str) = ft_buf_flush(&(s.buffer))))
		return (-1);
	if (s.cursorpos)
		add_to_command_hist(input->str);
	input->save = &(input->str[0]);
	ft_buf_destroy(&(s.buffer));
	return (s.c[3]);
}
