/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_homeend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 11:23:11 by amordret          #+#    #+#             */
/*   Updated: 2018/09/18 11:29:02 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_end(t_read_input *s)
{
	while (s->cursorpos < g_termcaps.writtenchars)
	{
		ft_putstr_fd(g_termcaps.cursorright, 0);
		s->cursorpos++;
	}
}

void	input_is_home(t_read_input *s)
{
	while (s->cursorpos > 0)
	{
		ft_putstr_fd(g_termcaps.cursorleft, 0);
		s->cursorpos--;
	}
}