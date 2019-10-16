/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:17:55 by amordret          #+#    #+#             */
/*   Updated: 2019/10/16 15:08:51 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		input_is_ctrld(t_read_input *s, int *cursorpos, t_buf *buffer)
{
	if (g_termcaps.writtenchars == 0)
	{
		if (g_termcaps.promptlength < 3)
			return (input_is_ctrlc(s));
		else
		{
			ft_putstr("exit\n");
			termcaps_reset_term_and_exit(0);
		}
	}
	if (*cursorpos == buffer->i)
		return (0);
	ft_buf_delete_char(buffer, *(cursorpos));
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	if (g_termcaps.writtenchars)
		g_termcaps.writtenchars--;
	return (0);
}

int		input_is_ctrlc(t_read_input *s)
{
	input_is_end(s);
	if (g_termcaps.promptlength < 5)
		ft_putchar_fd('\n', g_termcaps.fd);
	return (-1);
}
