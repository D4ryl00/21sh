/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:49:18 by amordret          #+#    #+#             */
/*   Updated: 2019/10/11 11:57:46 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** "line" contains previous shell commands terminated or not by a final newline.
** So the above function removes the final newline to this string
** if there is it.
*/

void		add_to_command_hist(char *line)
{
	t_command_history	*new_element;
	unsigned int		i;
	size_t				line_length;
	int					has_newline;

	i = -1;
	if (!line)
		return (term_putstr(ERR_COM_HIST));
	line_length = ft_strlen(line);
	has_newline = line[line_length - 1] == '\n' ? 1 : 0;
	if (!(new_element = malloc(sizeof(*new_element)))
	|| !(new_element->command = malloc(sizeof(char) *
	(line_length + (has_newline ? 0 : 1)))))
		return (term_putstr(ERR_COM_HIST));
	while (++i < line_length)
		new_element->command[i] = line[i];
	new_element->command[has_newline ? i - 1 : i] = '\0';
	new_element->next = g_first_cmd_history;
	g_first_cmd_history = new_element;
}

static void	savehisttofile2(int fd, t_command_history *c, t_command_history *p)
{
	int	i;

	i = 0;
	c = g_first_cmd_history;
	while (c->next && ++i < MAX_HISTORY)
	{
		p = c;
		c = c->next;
	}
	if (i == MAX_HISTORY)
		free_minilibx(c->next);
	ft_putendl_fd(c->command, fd);
	if (c->command)
		free(c->command);
	free(c);
	if (p)
		p->next = NULL;
	if (c == g_first_cmd_history)
		g_first_cmd_history = NULL;
}

void		save_hist_to_file(void)
{
	int					fd;
	t_command_history	*current_element;
	t_command_history	*previous_element;

	previous_element = NULL;
	current_element = NULL;
	if ((fd = open_history_file(1)) < 1)
		return ;
	while (g_first_cmd_history)
		savehisttofile2(fd, current_element, previous_element);
	close_history_file(fd);
}

void		save_current_hist(t_read_input *s)
{
	int					i;
	t_command_history	*current_element;

	i = 0;
	if (g_first_cmd_history == NULL)
		return ;
	current_element = g_first_cmd_history;
	if (s->historynb < 1)
		return ;
	while (++i < s->historynb && current_element->next)
		current_element = current_element->next;
	if (current_element->command)
		free(current_element->command);
	current_element->command = ft_strdup(((s->buffer).buf));
}

void		fill_command_hist(void)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = 0;
	if (g_first_cmd_history)
		return ;
	g_first_cmd_history = NULL;
	fd = open_history_file(0);
	while (get_next_line(fd, &line))
	{
		add_to_command_hist(line);
		if (line)
			free(line);
	}
	close_history_file(fd);
}
