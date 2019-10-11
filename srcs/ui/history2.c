/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:37:30 by amordret          #+#    #+#             */
/*   Updated: 2019/10/11 11:58:10 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	append_line_to_prev_hist(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	if (!(line) || !(g_first_cmd_history) || !(g_first_cmd_history->command) ||
	(tmp =
	malloc(ft_strlen(g_first_cmd_history->command) + ft_strlen(line) + 1)) ==
	NULL)
		return ;
	while (g_first_cmd_history->command[++i])
		tmp[++j] = g_first_cmd_history->command[i];
	tmp[++j] = '\n';
	i = -1;
	while (line[++i] && line[i] != '\n')
		tmp[++j] = line[i];
	tmp[++j] = '\0';
	free(g_first_cmd_history->command);
	g_first_cmd_history->command = tmp;
}

int		max_history_reached(t_read_input *s)
{
	int					i;
	t_command_history	*current;

	i = 0;
	if (!(g_first_cmd_history))
		return (0);
	current = g_first_cmd_history;
	while (current)
	{
		current = current->next;
		i++;
	}
	if (i >= s->historynb + 1)
		return (0);
	else
		return (1);
}

void	free_minilibx(t_command_history *lasthistory)
{
	t_command_history	*next_element;

	if (lasthistory && lasthistory->command)
		while (lasthistory)
		{
			next_element = lasthistory->next;
			lasthistory->next = NULL;
			free(lasthistory->command);
			free(lasthistory);
			lasthistory = next_element;
		}
}
