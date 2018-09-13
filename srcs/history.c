/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:49:18 by amordret          #+#    #+#             */
/*   Updated: 2018/09/13 15:36:25 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	open_history_file(void)
{
	char	*historyfilepath;
	int		fd;

	fd = 0;
	historyfilepath = ft_memalloc(ft_strlen(getenv("HOME")) + 5);
	ft_strcat(historyfilepath, getenv("HOME"));
	ft_strcat(historyfilepath, "/.21sh");

	if ((fd = open(historyfilepath,
	O_RDWR | O_CREAT | O_APPEND, S_IRWXG | S_IRWXO | S_IRWXU)) < 1)
		termcaps_echoandputstr(ERR_READ);

	/*if ((s->fd_history = open(historyfilepath,
	O_RDWR | O_APPEND )) < 1)
		return (termcaps_echoandputstr(ERR_READ));*/
	free(historyfilepath);
	return (fd);
}

static void	close_history_file(int fd)
{
	if (fd > 1)
		if ((close(fd)) == -1)
			termcaps_echoandputstr(ERR_CLOSE);
}

void	add_to_command_hist(char *line)
{
	t_command_history *new_element;

//	if (first_command_hist == NULL)
//		return termcaps_echoandputstr(ERR_COM_HIST);
	if ((new_element = malloc(sizeof(*new_element))) == NULL)
		return (termcaps_echoandputstr(ERR_COM_HIST));
	new_element->command = ft_strdup(line);
	new_element->next = g_first_cmd_history;
	g_first_cmd_history = new_element;
}

void	fill_command_hist(void)
{
	char	*line;
	int		fd;
	
	line = NULL;
	fd = 0;

	if (g_first_cmd_history)
		return ;
	if ((g_first_cmd_history = malloc(sizeof(t_command_history*))) == NULL)
		return (termcaps_echoandputstr(ERR_COM_HIST));
	g_first_cmd_history = NULL;
	fd = open_history_file();
	while (get_next_line(fd, &line))
	{
		add_to_command_hist(line);
		if (line)
			free(line);
	}
	close_history_file(fd);
}
