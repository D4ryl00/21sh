/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 15:44:08 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 16:02:55 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_compound_list(t_ast_compound_list **cl, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*cl = (t_ast_compound_list *)malloc(sizeof(t_ast_compound_list))))
			exit_perror(ENOMEM, NULL);
		(*cl)->linebreak = NULL;
		(*cl)->term = NULL;
		(*cl)->separator = NULL;
		ast_linebreak(&((*cl)->linebreak), tokens);
		if ((status = ast_term(&((*cl)->term), tokens)) < 1)
		{
			free_ast_compound_list(*cl);
			cl = NULL;
			return (status);
		}
		ast_separator(&((*cl)->separator), tokens);
		return (1);
	}
	return (0);
}

void	free_ast_compound_list(t_ast_compound_list *cl)
{
	if (cl)
	{
		if (cl->linebreak)
			free_ast_linebreak(cl->linebreak);
		if (cl->term)
			free_ast_term(cl->term);
		if (cl->separator)
			free_ast_separator(cl->separator);
		free(cl);
	}
}
