/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:59:34 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/08 16:37:41 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_command(t_ast_command **command, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*command = (t_ast_command *)malloc(sizeof(t_ast_command))))
			exit_perror(ENOMEM, NULL);
		(*command)->simple_command = NULL;
		(*command)->redirect_list = NULL;
		if ((status = ast_simple_command(&((*command)->simple_command)
						, tokens)) < 1)
		{
			free_ast_command(*command);
			*command = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}
void	free_ast_command(t_ast_command *command)
{
	if (command)
	{
		if (command->simple_command)
			free_ast_simple_command(command->simple_command);
		free(command);
	}
}
