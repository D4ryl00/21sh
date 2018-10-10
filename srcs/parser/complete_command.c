/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:10:27 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/09 06:21:17 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_complete_command(t_ast_complete_command **cc, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*cc = (t_ast_complete_command *)malloc(
						sizeof(t_ast_complete_command))))
			exit_perror(ENOMEM, NULL);
		(*cc)->list = NULL;
		(*cc)->separator_op = NULL;
		if ((status = ast_list(&((*cc)->list), tokens)) > 0)
			ast_separator_op(&((*cc)->separator_op), tokens);
		else
		{
			free_ast_complete_command(*cc);
			*cc = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_complete_command(t_ast_complete_command *cc)
{
	if (cc)
	{
		if (cc->list)
			free_ast_list(cc->list);
		if (cc->separator_op)
			free_ast_separator_op(cc->separator_op);
		free(cc);
	}
}
