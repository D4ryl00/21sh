/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:08:19 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:12:33 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_and_or(t_ast_and_or **and_or, t_list **tokens)
{
	int		status;
	t_list	*save;

	save = *tokens;
	if (*tokens)
	{
		if (!(*and_or = (t_ast_and_or *)malloc(sizeof(t_ast_and_or))))
			exit_perror(ENOMEM, NULL);
		(*and_or)->pipeline = NULL;
		(*and_or)->linebreak = NULL;
		(*and_or)->and_or = NULL;
		(*and_or)->op = TOKEN;
		if ((status = ast_pipeline(&((*and_or)->pipeline), tokens)) > 0)
		{
			if (*tokens && ((((t_token *)(*tokens)->content)->type == AND_IF)
					|| (((t_token *)(*tokens)->content)->type == OR_IF)))
			{
				(*and_or)->op = ((t_token *)(*tokens)->content)->type;
				*tokens = (*tokens)->next;
				ast_linebreak(&((*and_or)->linebreak), tokens);
				if (!*tokens && get_new_tokens(tokens, save) == -1)
					return (-1);
				if (ast_and_or(&((*and_or)->and_or), tokens) < 1)
				{
					free_ast_and_or(*and_or);
					*and_or = NULL;
					return (-1);
				}
			}
		}
		else
		{
			free_ast_and_or(*and_or);
			*and_or = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_and_or(t_ast_and_or *and_or)
{
	if (and_or)
	{
		if (and_or->pipeline)
			free_ast_pipeline(and_or->pipeline);
		if (and_or->linebreak)
			free_ast_linebreak(and_or->linebreak);
		if (and_or->and_or)
			free_ast_and_or(and_or->and_or);
		free(and_or);
	}
}
