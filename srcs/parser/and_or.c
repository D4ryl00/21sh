/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:08:19 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 16:47:05 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** t_ast_and_or init with default values
*/

static void	ast_and_or_init(t_ast_and_or *and_or)
{
	if (and_or)
	{
		and_or->pipeline = NULL;
		and_or->linebreak = NULL;
		and_or->and_or = NULL;
		and_or->op = NULL;
	}
}

/*
** Free the whole structure
*/

void		free_ast_and_or(t_ast_and_or *and_or)
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

/*
** Free the ast_and_or struct and set the pointer NULL.
*/

static int	ast_and_or_error(t_ast_and_or **and_or, int status)
{
	if (and_or && *and_or)
	{
		free_ast_and_or(*and_or);
		*and_or = NULL;
	}
	return (status);
}

/*
** It's called when the input line contain a && or ||
** Evaluate the 2nd part of the operator.
** Call a new prompt if needed.
*/

static int	ast_and_or_next(t_ast_and_or **and_or, t_list **tokens
		, t_list *save)
{
	if (!((*and_or)->op = ft_strdup(((t_token *)(*tokens)->content)->content)))
		exit_perror(ENOMEM, NULL);
	*tokens = (*tokens)->next;
	ast_linebreak(&((*and_or)->linebreak), tokens);
	while (!*tokens)
	{
		if (!*tokens && get_new_tokens(tokens, save) == -1)
			return (ast_and_or_error(and_or, -1));
		ast_linebreak(&((*and_or)->linebreak), tokens);
	}
	if (ast_and_or(&((*and_or)->and_or), tokens) < 1)
		return (ast_and_or_error(and_or, -1));
	return (0);
}

/*
** and_or (see shell grammar)
*/

int			ast_and_or(t_ast_and_or **and_or, t_list **tokens)
{
	int		status;
	t_list	*save;

	save = *tokens;
	if (*tokens)
	{
		if (!(*and_or = (t_ast_and_or *)malloc(sizeof(t_ast_and_or))))
			exit_perror(ENOMEM, NULL);
		ast_and_or_init(*and_or);
		if ((status = ast_pipeline(&((*and_or)->pipeline), tokens)) > 0)
		{
			if (*tokens && (!ft_strcmp(((t_token *)(*tokens)->content)->content
							, "&&")
					|| !ft_strcmp(((t_token *)(*tokens)->content)->content
						, "||")))
				if (ast_and_or_next(and_or, tokens, save) == -1)
					return (-1);
		}
		else
			return (ast_and_or_error(and_or, status));
		return (1);
	}
	return (0);
}
