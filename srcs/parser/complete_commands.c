/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:11:28 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 06:23:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

static void	ast_complete_commands_init(t_ast_complete_commands *cc)
{
	if (cc)
	{
		cc->complete_command = NULL;
		cc->newline_list = NULL;
		cc->complete_commands = NULL;
	}
}

void		free_ast_complete_commands(t_ast_complete_commands *cc)
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

static int	ast_complete_commands_error(t_ast_complete_commands **cc
		, int status)
{
	if (cc && *cc)
	{
		free_ast_complete_commands(*cc);
		*cc = NULL;
	}
	return (status);
}

int			ast_complete_commands(t_ast_complete_commands **cc, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*cc = (t_ast_complete_commands *)malloc(
						sizeof(t_ast_complete_commands))))
			exit_perror(ENOMEM, NULL);
		ast_complete_commands_init(*cc);
		if ((status = ast_complete_command(&((*cc)->complete_command), tokens))
				> 0)
		{
			if (ast_newline_list(&((*cc)->newline_list), tokens))
			{
				if ((status = ast_complete_commands(&((*cc)->complete_commands)
								, tokens)) == -1)
					return (ast_complete_commands_error(cc, status));
			}
		}
		else
			return (ast_complete_commands_error(cc, status));
		return (1);
	}
	return (0);
}
