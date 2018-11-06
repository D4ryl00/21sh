/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:02:48 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/27 01:40:53 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_newline_list(t_ast_newline_list **nl_list, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*nl_list = (t_ast_newline_list *)malloc(
						sizeof(t_ast_newline_list))))
			exit_perror(ENOMEM, NULL);
		(*nl_list)->nl = '\0';
		(*nl_list)->newline_list = NULL;
		if (((t_token *)(*tokens)->content)->type == NEWLINE)
		{
			(*nl_list)->nl = '\n';
			*tokens = (*tokens)->next;
			ast_newline_list(&((*nl_list)->newline_list), tokens);
		}
		else
		{
			free_ast_newline_list(*nl_list);
			*nl_list = NULL;
			return (-1);
		}
		return (1);
	}
	return (0);
}

void	free_ast_newline_list(t_ast_newline_list *newline_list)
{
	if (newline_list)
	{
		if (newline_list->newline_list)
			free_ast_newline_list(newline_list->newline_list);
		free(newline_list);
	}
}
