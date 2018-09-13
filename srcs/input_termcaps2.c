/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcaps2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:00:53 by amordret          #+#    #+#             */
/*   Updated: 2018/09/13 16:37:01 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_up(t_read_input *s)
{
	int	i;

	i = -1;
	if (termcaps_clearline(s) == -1)
		return ;
	//fill_command_hist(s);
	if (g_first_cmd_history)
	{
		add_to_command_hist(s->buffer.buf);
		ft_buf_destroy(&(s->buffer));
		ft_buf_init(&(s->buffer));
		while (g_first_cmd_history->command[i++])
		{
			if ((ft_buf_insert_char(&(s->buffer), g_first_cmd_history->command[i], i)) == -1)
				exit_perror(EBUFF, NULL);				
		}
		termcaps_echoandputstr((g_first_cmd_history->next->command));
		s->cursorpos = ft_strlen(g_first_cmd_history->next->command);
	}
	/*while (((*(s->first_command_hist))->command)[i])
	{
		if (ft_buf_insert_char(&(s->buffer),(((*(s->first_command_hist))->command)[i]) , i) == 0)
			return ;
		i++;
	}*/
}
