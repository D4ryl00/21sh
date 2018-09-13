/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcaps2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:00:53 by amordret          #+#    #+#             */
/*   Updated: 2018/09/13 15:27:50 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_up(t_read_input *s)
{
	int					i;

	i = 0;
	if (termcaps_clearline(s) == -1)
		return ;
	//fill_command_hist(s);
	if (*(s->first_command_hist))
	{
		termcaps_echoandputstr((*(s->first_command_hist))->command);
		s->cursorpos = ft_strlen((*(s->first_command_hist))->command);
	}
	/*while (((*(s->first_command_hist))->command)[i])
	{
		if (ft_buf_insert_char(&(s->buffer),(((*(s->first_command_hist))->command)[i]) , i) == 0)
			return ;
		i++;
	}*/
}
