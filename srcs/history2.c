/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:37:30 by amordret          #+#    #+#             */
/*   Updated: 2018/09/19 10:51:18 by amordret         ###   ########.fr       */
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
