/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:11:28 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 08:12:25 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int		ast_complete_commands(t_ast_complete_commands **cc, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*cc = (t_ast_complete_commands *)malloc(
						sizeof(t_ast_complete_commands))))
			exit_perror(ENOMEM, NULL);
		(*cc)->complete_command = NULL;
		(*cc)->newline_list = NULL;
		(*cc)->complete_commands = NULL;
		if ((status = ast_complete_command(&((*cc)->complete_command), tokens)) > 0)
		{
			if (ast_newline_list(&((*cc)->newline_list), tokens))
			{
				if ((status = ast_complete_commands(&((*cc)->complete_commands), tokens)) == -1)
				{
					free_ast_complete_commands(*cc);
					*cc = NULL;
					return (status);
				}
			}
		}
		else
		{
			free_ast_complete_commands(*cc);
			*cc = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_complete_commands(t_ast_complete_commands *cc)
{
	if (cc)
	{
		if (cc->complete_command)
			free_ast_complete_command(cc->complete_command);
		if (cc->newline_list)
			free_ast_newline_list(cc->newline_list);
		if (cc->complete_commands)
			free_ast_complete_commands(cc->complete_commands);
		free(cc);
	}
}
