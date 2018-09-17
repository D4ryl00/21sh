/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_termcaps2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:00:53 by amordret          #+#    #+#             */
/*   Updated: 2018/09/17 15:10:38 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	input_is_up(t_read_input *s)
{
	int					i;
	t_command_history	*current_element;

	i = 0;
	if (termcaps_clearline(s) == -1)
		return ;
	if (g_first_cmd_history)
	{
		if (s->historynb)
			save_current_hist(s);
		s->historynb++;
		current_element = g_first_cmd_history;
		while (++i < s->historynb && current_element->next)
			current_element = current_element->next;
		i = -1;
		/*if (s->historynb == 1)
			add_to_command_hist(s->buffer.buf);*/
		ft_buf_destroy(&(s->buffer));
		ft_buf_init(&(s->buffer));
		while (current_element->command[++i])
		{
			if ((ft_buf_insert_char(&(s->buffer), (current_element->command)[i], i)) == -1)
				exit_perror(EBUFF, NULL);				
		}
		term_putstr((current_element->command));
		s->cursorpos = ft_strlen(current_element->command);

	}
}
