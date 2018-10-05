/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:24:09 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 08:24:22 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int		ast_separator_op(t_ast_separator_op **s_op, t_list **tokens)
{
	if (*tokens)
	{
		if (!(*s_op = (t_ast_separator_op *)malloc(sizeof(t_ast_separator_op))))
			exit_perror(ENOMEM, NULL);
		(*s_op)->c = ((t_token *)(*tokens)->content)->content[0];
		if (((*s_op)->c != '&') && ((*s_op)->c != ';'))
		{
			free_ast_separator_op(*s_op);
			*s_op = NULL;
			return (0);
		}
		*tokens = (*tokens)->next;
		return (1);
	}
	return (0);
}

void	free_ast_separator_op(t_ast_separator_op *s_op)
{
	if (s_op)
	{
		free(s_op);
	}
}
