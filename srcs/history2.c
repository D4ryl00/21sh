/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:37:30 by amordret          #+#    #+#             */
/*   Updated: 2018/09/19 11:18:17 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	max_history_reached(t_read_input *s)
{
	int					i;
	t_command_history	*current;

	i = 0;
	if (!(g_first_cmd_history))
		return (0);
	current = g_first_cmd_history;
	while(current)
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
