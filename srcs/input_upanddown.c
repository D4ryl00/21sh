/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_upanddown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:00:53 by amordret          #+#    #+#             */
/*   Updated: 2018/09/19 11:29:41 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern void	recall_tmpline(t_read_input *s)
{
	int	i;

	i = -1;
	if (s->historynb == 1 && s->tmpline)
	{
		save_current_hist(s);
		ft_buf_destroy(&(s->buffer));
		ft_buf_init(&(s->buffer));
		while (s->tmpline[++i])
			if ((ft_buf_insert_char(&(s->buffer), (s->tmpline)[i], i)) == -1)
				exit_perror(EBUFF, NULL);
		term_putstr((s->tmpline));
		s->cursorpos = ft_strlen(s->tmpline);
		free(s->tmpline);
		s->historynb--;
	}
	else
	{
		ft_buf_destroy(&(s->buffer));
		ft_buf_init(&(s->buffer));
	}
	return ;
}

void		input_is_down(t_read_input *s)
{
	int					i;
	t_command_history	*current_element;

	i = 0;
	termcaps_clearline(s);
	if (s->historynb == 1)
		return (recall_tmpline(s));
	if (g_first_cmd_history)
	{
		if (s->historynb)
			save_current_hist(s);
		current_element = g_first_cmd_history;
		s->historynb--;
		while (++i < s->historynb && current_element->next)
			current_element = current_element->next;
		i = -1;
		ft_buf_destroy(&(s->buffer));
		ft_buf_init(&(s->buffer));
		while (current_element->command[++i])
			if ((ft_buf_insert_char(&(s->buffer),
			(current_element->command)[i], i)) == -1)
				exit_perror(EBUFF, NULL);
		term_putstr((current_element->command));
		s->cursorpos = ft_strlen(current_element->command);
	}
}

void		input_is_up(t_read_input *s)
{
	int					i;
	t_command_history	*current_element;

	i = 0;
	if (g_first_cmd_history && termcaps_clearline(s) == 0)
	{
		if (!(s->historynb))
			s->tmpline = ft_buf_flush(&(s->buffer));
		else
			save_current_hist(s);
		current_element = g_first_cmd_history;
		while (++i < (s->historynb + 1) && current_element->next)
			current_element = current_element->next;
		i = -1;
		if (current_element)
			s->historynb++;
		ft_buf_destroy(&(s->buffer));
		ft_buf_init(&(s->buffer));
		while (current_element->command[++i])
			if ((ft_buf_insert_char(&(s->buffer),
			(current_element->command)[i], i)) == -1)
				exit_perror(EBUFF, NULL);
		term_putstr((current_element->command));
		s->cursorpos = ft_strlen(current_element->command);
	}
}
