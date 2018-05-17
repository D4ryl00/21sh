/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:49:18 by amordret          #+#    #+#             */
/*   Updated: 2018/05/17 14:26:18 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	open_history_file(t_read_input *s)
{
	char	*historyfilepath;

	historyfilepath = ft_memalloc(ft_strlen(getenv("HOME")) + 5);
	ft_strcat(historyfilepath, getenv("HOME"));
	ft_strcat(historyfilepath, "/.21sh");
	
	/*if ((s->fd_history = open("~/.21sh",
	O_RDWR | O_CREAT | O_APPEND | S_IRWXG | S_IRWXO | S_IRWXU)) < 1)
		termcaps_echoandputstr(ERR_READ);
*/
	if ((s->fd_history = open(historyfilepath,
	O_RDWR | O_APPEND )) < 1)
		return (termcaps_echoandputstr(ERR_READ));
	free(historyfilepath);
}

static void	close_history_file(t_read_input *s)
{
	if (s->fd_history > 1)
		if ((close(s->fd_history)) == -1)
			termcaps_echoandputstr(ERR_CLOSE);
}

void	add_to_command_hist(t_command_history **first_command_hist, char *line)
{
	t_command_history *new_element;

	if (first_command_hist == NULL)
		return termcaps_echoandputstr(ERR_COM_HIST);
	if ((new_element = malloc(sizeof(*new_element))) == NULL)
		return (termcaps_echoandputstr(ERR_COM_HIST));
	new_element->command = ft_strdup(line);
	new_element->next = *(first_command_hist);
	*(first_command_hist) = new_element;
}

void	fill_command_hist(t_read_input *s)
{
	char	*line;
	
	if (s->first_command_hist)
		return ;
	if ((s->first_command_hist = malloc(sizeof(t_command_history*))) == NULL)
		return (termcaps_echoandputstr(ERR_COM_HIST));
	*(s->first_command_hist) = NULL;
	open_history_file(s);
	while (get_next_line(s->fd_history, &line))
	{
		add_to_command_hist(s->first_command_hist, line);
		free(line);
	}
	close_history_file(s);
}
