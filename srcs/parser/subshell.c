/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 12:24:59 by rbarbero          #+#    #+#             */
/*   Updated: 2018/11/02 16:43:32 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"
#include "parser.h"

void	free_ast_subshell(t_ast_subshell *subshell)
{
	if (subshell)
	{
		if (subshell->compound_list)
			free_ast_compound_list(subshell->compound_list);
		free(subshell);
	}
}

int		ast_subshell(t_ast_subshell **subshell, t_list **tokens)
{
	int	status;

	if (*tokens)
	{
		if (!ft_strcmp(((t_token *)(*tokens)->content)->content, "("))
		{
			if (!(*subshell = (t_ast_subshell *)malloc(sizeof(t_ast_subshell))))
				exit_perror(ENOMEM, NULL);
			(*subshell)->compound_list = NULL;
			*tokens = (*tokens)->next;
			if (((status = ast_compound_list(&((*subshell)->compound_list)
							, tokens)) < 1) || (ft_strcmp(
							((t_token *)(*tokens)->content)->content, ")")))
			{
				free_ast_subshell(*subshell);
				*subshell = NULL;
				return (status);
			}
			*tokens = (*tokens)->next;
			return (1);
		}
	}
	return (0);
}
