/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 12:10:59 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 15:45:01 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_compound_command(t_ast_compound_command **cc, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*cc = (t_ast_compound_command *)malloc(
						sizeof(t_ast_compound_command))))
			exit_perror(ENOMEM, NULL);
		(*cc)->subshell = NULL;
		if ((status = ast_subshell(&((*cc)->subshell), tokens)) < 1)
		{
			free_ast_compound_command(*cc);
			*cc = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_compound_command(t_ast_compound_command *cc)
{
	if (cc)
	{
		if (cc->subshell)
			free_ast_subshell(cc->subshell);
		free(cc);
	}
}
