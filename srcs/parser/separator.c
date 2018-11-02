/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 16:17:17 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 16:40:21 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_separator(t_ast_separator **separator, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*separator = (t_ast_separator *)malloc(sizeof(t_ast_separator))))
			exit_perror(ENOMEM, NULL);
		(*separator)->linebreak = NULL;
		(*separator)->separator_op = NULL;
		(*separator)->newline_list = NULL;
		if ((status = ast_separator_op(&((*separator)->separator_op), tokens))
				> 0)
			ast_linebreak(&((*separator)->linebreak), tokens);
		else if (!status)
			status = ast_newline_list(&((*separator)->newline_list), tokens);
		if (status < 1)
		{
			free_ast_separator(*separator);
			*separator = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_separator(t_ast_separator *separator)
{
	if (separator)
	{
		if (separator->separator_op)
			free_ast_separator_op(separator->separator_op);
		if (separator->linebreak)
			free_ast_linebreak(separator->linebreak);
		if (separator->newline_list)
			free_ast_newline_list(separator->newline_list);
		free(separator);
	}
}
