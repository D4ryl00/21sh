/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:17:55 by amordret          #+#    #+#             */
/*   Updated: 2019/10/11 11:58:48 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_ctrld(int *cursorpos, t_buf *buffer)
{
	if (*cursorpos == buffer->i)
		return ;
	ft_buf_delete_char(buffer, *(cursorpos));
	ft_putstr_fd(g_termcaps.delete, g_termcaps.fd);
	if (g_termcaps.writtenchars)
		g_termcaps.writtenchars--;
}

int		input_is_ctrlc(t_read_input *s)
{
	input_is_end(s);
	return (0);
}
