/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 07:59:34 by rbarbero          #+#    #+#             */
/*   Updated: 2019/10/11 17:58:04 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Currently, simple_command returns -1 when bad token is occured. Further,
** it shall return 0 to tell that it's not a simple command and there is not
** any error. Of course, if there is an error, it shall return -1.
*/

int		ast_command(t_ast_command **command, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*command = (t_ast_command *)malloc(sizeof(t_ast_command))))
			exit_perror(ENOMEM, NULL);
		(*command)->simple_command = NULL;
		(*command)->compound_command = NULL;
		(*command)->redirect_list = NULL;
		if ((status = ast_simple_command(&((*command)->simple_command)
						, tokens)) > 0)
			return (1);
		else if (status >= 0 && (status =
					ast_compound_command(&((*command)->compound_command)
						, tokens)) > 0)
			return (1);
		else
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
