/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbero <rbarbero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 05:56:08 by rbarbero          #+#    #+#             */
/*   Updated: 2018/10/05 21:52:05 by rbarbero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int		ast_cmd_word(t_ast_cmd_word **word, t_list **tokens)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type == TOKEN)
	{
		if (!(*word = (t_ast_cmd_word *)malloc(sizeof(t_ast_cmd_word))))
			exit_perror(ENOMEM, NULL);
		if (!((*word)->word = ft_strdup(((t_token *)(*tokens)->content)->content)))
			exit_perror(ENOMEM, NULL);
		*tokens = (*tokens)->next;
		return (1);
	}
	ft_perror(ESYNT, *tokens ? ((t_token *)(*tokens)->content)->content : "NULL"
			, 1);
	return (-1);
}

void	free_ast_cmd_word(t_ast_cmd_word *cmd_word)
{
	if (cmd_word)
	{
		if (cmd_word->word)
			free(cmd_word->word);
		free(cmd_word);
	}
}
