/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 16:03:19 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 16:15:25 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

/*
** Free a ast_list and set pointer to NULL.
*/

static int	ast_term_error(t_ast_term **term, int status)
{
	if (term && *term)
	{
		free_ast_term(*term);
		*term = NULL;
	}
	return (status);
}

int		ast_term(t_ast_term **term, t_list **tokens)
{
	int		status;
	t_list	*save;

	if (*tokens)
	{
		if (!(*term = (t_ast_term *)malloc(sizeof(t_ast_term))))
			exit_perror(ENOMEM, NULL);
		(*term)->and_or = NULL;
		(*term)->separator = NULL;
		(*term)->term = NULL;
		if ((status = ast_and_or(&((*term)->and_or), tokens)) > 0)
		{
			save = *tokens;
			if (ast_separator(&((*term)->separator), tokens))
			{
				if ((status = ast_term(&((*term)->term), tokens)) == -1)
					*tokens = save;
			}
		}
		else
			return (ast_term_error(term, status));
		return (1);
	}
	return (0);
}

void	free_ast_term(t_ast_term *term)
{
	if (term)
	{
		if (term->and_or)
			free_ast_and_or(term->and_or);
		if (term->separator)
			free_ast_separator(term->separator);
		if (term->term)
			free_ast_term(term->term);
		free(term);
	}
}
