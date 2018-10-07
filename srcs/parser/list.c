/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:09:21 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/07 12:14:34 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

int		ast_list(t_ast_list **list, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!(*list = (t_ast_list *)malloc( sizeof(t_ast_list))))
			exit_perror(ENOMEM, NULL);
		(*list)->and_or = NULL;
		(*list)->separator_op = NULL;
		(*list)->list = NULL;
		if ((status = ast_and_or(&((*list)->and_or), tokens)) > 0)
		{
			if (ast_separator_op(&((*list)->separator_op), tokens))
			{
				if ((status = ast_list(&((*list)->list), tokens)) == -1)
				{
					free_ast_list(*list);
					*list = NULL;
					return (status);
				}
			}
		}
		else
		{
			free_ast_list(*list);
			*list = NULL;
			return (status);
		}
		return (1);
	}
	return (0);
}

void	free_ast_list(t_ast_list *list)
{
	if (list)
	{
		if (list->and_or)
			free_ast_and_or(list->and_or);
		if (list->separator_op)
			free_ast_separator_op(list->separator_op);
		if (list->list)
			free_ast_list(list->list);
		free(list);
	}
}
